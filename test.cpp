/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:33:04 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/07/26 17:04:56 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"

// Helper function to retrieve channel members
std::vector<Client*> getChannelMembers(Channel *channel)
{
	// Assuming Channel has a method to expose its members
	return channel->getMembers();
}

void	Server::handleJoin(int clientFd, std::vector<std::string> &tokens)
{
	if (tokens.size() < 2)
	{
		sendMsg(clientFd, "Usage: JOIN <#channel>\n");
		return;
	}
	std::string channelName = tokens[1];
	if (channelName[0] != '#')
	{
		sendMsg(clientFd, "Channel names must start with '#'\n");
		return;
	}
	Channel *channel;
	if (channels.count(channelName))
	{
		channel = channels[channelName];
	}
	else
	{
		channel = new Channel(channelName);
		channels[channelName] = channel;
		std::cout << "Created new channel: " << channelName << std::endl;
	}
	Client *client = getClientFd(clientFd);
	if (!client)
	{
		std::cerr << "Client not found for fd: " << clientFd << std::endl;
		return;
	}
	if (channel->isMember(client))
	{
		sendMsg(clientFd, "You are already in channel " + channelName + "\n");
		return;
	}
	channel->addClient(client);
	sendMsg(clientFd, "You have joined " + channelName + "\n");
}

void	Server::handleUser(int clientFd, std::vector<std::string> &tokens)
{
	Client *targetClientFd = getClientFd(clientFd);
	if (!targetClientFd)
	{
		std::cerr << "Client's fd not found: " << targetClientFd << std::endl;
		return;
	}
	targetClientFd->setUsername(tokens[1]);
	std::string ackMessage = "The username has been set!\n";
	sendMsg(clientFd, ackMessage);
}

Channel	*Server::getChannel(const std::string &name)
{
	for (std::map<std::string, Channel*>::const_iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if (it->second->getName() == name)
			return it->second;
	}
	return nullptr;
}


void	Server::handleChannelmsg(int clientFd, std::vector<std::string> &tokens)
{
	Channel	*channel = getChannel(tokens[1]);
	if (channel)
	{
		std::vector<Client*> members = getChannelMembers(channel);
		for (std::vector<Client*>::const_iterator it = members.begin(); it != members.end(); ++it)
		{
			Client *member = *it;
			int memberFd = member->getFd();
			// Example: Send a message to each member
			sendMsg(memberFd, "Broadcast message to channel members\n");
		}
		return;
	}
	sendMsg(clientFd, "Channel must exist, in order to send message to it!\n");
}

void	Server::handlePrivmsg(int clientFd, std::vector<std::string> &tokens)
{
	if (tokens.size() < 3)
	{
		std::cerr << "PRIVMSG requires arguments: <nickname/channel> <message>" << std::endl;
		return;
	}
	if (tokens[1][0] == '#')
	{
		handleChannelmsg(clientFd, tokens);
		return;
	}
	Client *receiverClient = getClient(tokens[1]);

	if (!receiverClient)
	{
		std::cerr << "Nickname not found: " << tokens[1] << std::endl;
		return;
	}
	int	receiverFd = receiverClient->getFd();
	Client *senderClient = getClientFd(clientFd);
	std::string message = concatenateTokens(tokens);
	if(senderClient->getNickname().empty())
	{
		sendMsg(clientFd, "The nickname must be set in order to send messages!\n");
		return;
	}
	sendPrivMsg(receiverFd, clientFd, message);
}

void	Server::handleNick(int clientFd, std::vector<std::string> &tokens)
{
	Client *targetClientFd = getClientFd(clientFd);
	if (!targetClientFd)
	{
		std::cerr << "Client's fd not found: " << targetClientFd << std::endl;
		return;
	}
	time_t	currentTime = time(nullptr);
	if (targetClientFd->getLastNicknameChange() != 0)
	{
		double secondsSinceLastChange = difftime(currentTime, targetClientFd->getLastNicknameChange());
		if (secondsSinceLastChange < 7 * 24 * 60 * 60) // 7 dni
		{
			sendMsg(clientFd, "The Nickname can be only changed once every 7 days.\n");
			time_t sevenDays = 7 * 24 * 60 * 60;
			time_t timeLeft = sevenDays - secondsSinceLastChange;
			time_t timeLeftSeconds = timeLeft % (24 * 60 * 60);
			time_t timeLeftHours = timeLeftSeconds / (60 * 60);
			time_t timeLeftDays = timeLeft / (24 * 60 * 60);
			std::string timeLeftHoursString = std::to_string(timeLeftHours);
			std::string timeLeftDaysString = std::to_string(timeLeftDays);
			std::string timeLeftMsg = "The next available change for you is in ";
			timeLeftMsg += timeLeftDaysString;
			timeLeftMsg += " days, ";
			timeLeftMsg += timeLeftHoursString;
			timeLeftMsg += " hours!\n";
			sendMsg(clientFd, timeLeftMsg);
			return ;
		}
	}
	if (tokens[1][0] == '#')
	{
		sendMsg(clientFd, "Nickname cannot start with '#'!\n");
	}
	else if (checkNickname(tokens[1]))
	{
		targetClientFd->setNickname(tokens[1]);
		targetClientFd->setLastNicknameChange(currentTime);
		std::string ackMessage = "Welcome to the IRC server ";
		ackMessage += tokens[1];
		ackMessage += "!\n";
		sendMsg(clientFd, ackMessage);
	}
	else
	{
		sendMsg(clientFd, "The Nickname is already in use. Please use a different one!\n");
	}
	//std::cout << targetClientFd->getNickname() << std::endl;
}

void	Server::handleHelp(int clientFd)
{
	std::string helpMessage =
			"\nALL Commands have to be written exactly like below, in UPPERCASE letters format.\n"
			"\nALL COMMANDS:\n\n"
			"\tTHE FOLLOWING COMMANDS YOU NEED TO USE AFTER CONNECTING FOR THE FIRST TIME\n"
			"\tNICK <nickname> - set a nickname, visible for other users. Nickname can be changed only once every 7 days.\n"
			"\tUSER <username> - set a username, used only for server authentication\n\n"
			"\tOTHER AVAILABLE COMMANDS:\n"
			"\tPRIVMSG <nickname/channel> <message> - send a private message\n"
			"\tKICK <username> - eject a client from the channel\n"
			"\tINVITE <username> - invite a client to a channel\n"
			"\tTOPIC - change or view the channel topic\n"
			"\tMODE - change the channel's mode\n"
			"\t\t i: Set/remove Invite-only channel\n"
			"\t\t t: Set/remove the restrictions of the TOPIC \n"
			"\t\t k: Set/remove the channel key (password)\n"
			"\t\t o: Give/take channel operator privilege\n"
			"\t\t l: Set/remove the user limit to channel\n"
			"\tJOIN <channel> - join a specific channel\n"
			"\tQUIT - disconnect from the server\n";

		sendMsg(clientFd, helpMessage);
}

void	Server::handleInvite(int clientFd, Client &client, const std::vector<std::string> &tokens)
{
	std::cout << "INVITE command would be executed" << std::endl;
	(void)clientFd;
	(void)client;
	(void)tokens;
	//if(tokens.size() > 3 || tokens[1].empty() || tokens[2].empty())
	//{
	//	std::cerr << "INVITE requires arguments: <nickname>, <channel>" << std::endl;
	//}
	//else if (std::find(clients.begin(), clients.end(), client) != clients.end())
	//{
	//	std::cerr << "This operator client does not exist!" << std::endl;
	//}
	//else if (std::find(channels.begin(), channels.end(), tokens[2]) != channels.end())
	//{
	//	std::cerr << "This channel does not exist!" << std::endl;
	//}
	//Channel *channel = getChannel(tokens[2]);
	//if (!channel)
	//{
	//	return;
	//}
	//if (std::find(clients.begin(), clients.end(), tokens[1]) != clients.end())
	//{
	//	std::cerr << "The target client does not exist!" << std::endl;
	//}
	//if (!channel->isMember(&client) || !channel->isOperator(&client))
	//{
	//	std::cerr << "To invite others to a channel, the client must be an operator of this channel!" << std::endl;
	//	return;
	//}

	//std::cout << "The target client has now become the member of the channel." << std::endl;
}

//int Server::handleKick(int clientFd, Client &client, const std::vector<std::string> &tokens)
//{
//	if (!client.isOperator)
//	{
//		std::cerr << "Client " << clientFd << " is not an Operator." << std::endl;
//		std::cerr << "ONLY OPERATORS CAN USE KICK!" << std::endl;
//		return 0;
//	}
//	if(tokens[1].empty())
//	{
//		std::cerr << "KICK requires an argument!" << std::endl;
//		return 0;
//	}

//	const std::string &targerNickname = tokens[1];


//	else
//	{
//		if(tokens[1] == )
//	}
//}
