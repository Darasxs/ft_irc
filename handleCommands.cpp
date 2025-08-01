/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:33:04 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/08/01 21:46:33 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::handleTopic(int clientFd, const std::vector<std::string> &tokens)
{
	if (tokens.size() < 2)
	{
		sendMsg(clientFd, "Usage: TOPIC <#channel> <new topic>\n");
		return;
	}
	std::string channelName = tokens[1];
	if (channelName[0] != '#')
	{
		sendMsg(clientFd, "Invalid channel name.\n");
		return;
	}
	Channel* channel = getChannel(channelName);
	if (!channel)
	{
		sendMsg(clientFd, "Channel does not exist.\n");
		return;
	}
	Client* client = getClientFd(clientFd);
	if (!client)
	{
		sendMsg(clientFd, "Client not found.\n");
		return;
	}
	if (!channel->isMember(client))
	{
		sendMsg(clientFd, "You must be a member of the channel to view or set the topic.\n");
		return;
	}
	if (tokens.size() == 2)
	{
		std::string topic = channel->getTopic();
		if (topic.empty())
			sendMsg(clientFd, "No topic is set for " + channelName + ".\n");
		else
			sendMsg(clientFd, "Topic for " + channelName + ": " + topic + "\n");
		return;
	}
	if (channel->isTopicLocked() && !channel->isOperator(client))
	{
		sendMsg(clientFd, "Only operators can set the topic in this channel.\n");
		return;
	}
	std::string newTopic;
	for (size_t i = 2; i < tokens.size(); ++i)
	{
		newTopic += tokens[i];
		if (i + 1 != tokens.size())
			newTopic += " ";
	}
	channel->setTopic(newTopic);
}

void	Server::handleMode(int clientFd, std::vector<std::string> &tokens)
{
	if (tokens.size() < 3)
	{
		sendMsg(clientFd, "MODE requires arguments: <target> <mode>\n");
		return;
	}
	std::string target = tokens[1];
	Client* client = getClientFd(clientFd);
	if (!client)
	{
		sendMsg(clientFd, "Client not found.\n");
		return;
	}
	if (target.empty() || target[0] != '#')
	{
		sendMsg(clientFd, "Only channel modes supported.\n");
		return;
	}
	Channel* channel = nullptr;
	if (channels.count(target))
	{
		channel = channels[target];
	}
	else
	{
		sendMsg(clientFd, "Channel does not exist.\n");
		return;
	}
	if (!channel->isOperator(client))
	{
		sendMsg(clientFd, "You must be a channel operator to change modes.\n");
		return;
	}
	std::string modes = tokens[2];
	bool adding = true;
	size_t i = 0;
	char c = modes[i];
	if (c == '+')
	{
		adding = true;
	}
	else if (c == '-')
	{
		adding = false;
	}
	else
	{
		sendMsg(clientFd, "Unknown or unsupported mode\n");
		return ;
	}
	if (modes[i + 1])
	{
		c = modes[i + 1];
		if (c == 'i')
		{
			channel->setInviteOnly(adding);
			if (adding == true)
			{
				sendMsg(clientFd, "Invite-only mode enabled on " + target + "\n");
			}
			else
			{
				sendMsg(clientFd, "Invite-only mode disabled on " + target + "\n");
			}
		}
		else if (c == 't')
		{
			channel->setTopicRestrictions(adding);
			if (adding == true)
			{
				sendMsg(clientFd, "Topic Command restrictions are on " + target + "\n");
			}
			else
			{
				sendMsg(clientFd, "Topic Command restrictions are off " + target + "\n");
			}
		}
		else if (c == 'k')
		{
			if (adding == true)
			{
				if (!tokens[3].empty() && tokens[4].empty() && tokens[3][0] != '\0')
				{
					channel->setChannelKey(tokens[3]);
					sendMsg(clientFd, "The Channel Key is on " + target + "\n");
					channel->setKey(true);
				}
				else
				{
					sendMsg(clientFd, "Wrong arguments for 'k' mode" + target + "\n");
				}
			}
			else
			{
				channel->setChannelKey("");
				sendMsg(clientFd, "The Channel Key is off " + target + "\n");
			}
		}
		//else if (c == 'o')
		//{

		//	if (adding == true)
		//	{
		//		channel->setOperatorPrivilege(adding);
		//		sendMsg(clientFd, "The Operator Privilege is on " + target + "\n");
		//	}
		//	else
		//	{
		//		channel->setOperatorPrivilege(adding);
		//		sendMsg(clientFd, "The Operator Privilege is off " + target + "\n");
		//	}
		//}
		else if (c == 'l')
		{
			if (adding == true)
			{
				if (!tokens[3].empty() && tokens[4].empty() && !tokens[3][1] && tokens[3][0] >= '0' && tokens[3][0] <= '9')
				{
					channel->setUserLimit(std::stoi(tokens[3]));
					sendMsg(clientFd, "The User Limit is on " + target + "\n");
				}
				else
				{
					sendMsg(clientFd, "Wrong arguments for 'l' mode" + target + "\n");
				}
			}
			else
			{
				channel->setUserLimit(INT_MAX);
				sendMsg(clientFd, "The User Limit is off " + target + "\n");
			}
		}
		else
		{
			sendMsg(clientFd, "Unknown or unsupported mode\n");
		}
	}
	else
	{
		sendMsg(clientFd, "Unknown or unsupported mode\n");
	}
}

void	Server::handleKick(int clientFd, const std::vector<std::string> &tokens)
{
	if (tokens.size() < 3)
	{
		sendMsg(clientFd, "Usage: KICK <#channel> <nickname>\n");
		return;
	}
	std::string channelName = tokens[1];
	std::string targetNick = tokens[2];
	Client* requester = getClientFd(clientFd);
	if (!requester)
	{
		sendMsg(clientFd, "Your client could not be identified.\n");
		return;
	}
	if (channelName.empty() || channelName[0] != '#')
	{
		sendMsg(clientFd, "Invalid channel name.\n");
		return;
	}
	if (!channels.count(channelName))
	{
		sendMsg(clientFd, "Channel does not exist.\n");
		return;
	}
	if (requester->getNickname() == targetNick)
	{
		sendMsg(clientFd, "You cannot kick yourself.\n");
		return;
	}
	Channel* channel = channels[channelName];
	if (!channel->isOperator(requester))
	{
		sendMsg(clientFd, "You must be a channel operator to kick users.\n");
		return;
	}
	Client* targetUser = getClient(targetNick);
	if (!targetUser)
	{
		sendMsg(clientFd, "User " + targetNick + " not found.\n");
		return;
	}
	if (!channel->isMember(targetUser))
	{
		sendMsg(clientFd, targetNick + " is not in channel " + channelName + "\n");
		return;
	}
	channel->removeClient(targetUser);
	sendMsg(targetUser->getFd(), "You have been kicked from " + channelName + " by " + requester->getNickname() + "\n");
}

void	Server::handleInvite(int clientFd, std::vector<std::string> &tokens)
{
	if (tokens.size() < 3)
	{
		sendMsg(clientFd, "PRIVMSG requires arguments: <nickname/channel> <message>\n");
		return;
	}
	std::string targetNick = tokens[1];
	std::string channelName = tokens[2];
	if (channelName[0] != '#')
	{
		sendMsg(clientFd, "Channel name must start with '#'\n");
		return;
	}
	Client* inviter = getClientFd(clientFd);
	Client* invitee = getClient(targetNick);
	Channel* channel = getChannel(channelName);
	if (!invitee)
	{
		sendMsg(clientFd, "No such user\n");
		return;
	}
	if (!channel)
	{
		sendMsg(clientFd, "No such channel\n");
		return;
	}
	if (!channel->isMember(inviter))
	{
		sendMsg(clientFd, "You are not in the channel\n");
		return;
	}
	if (channel->isMember(invitee))
	{
		sendMsg(clientFd, "User is already in the channel\n");
		return;
	}
	if (channel->isInviteOnly() && !channel->isOperator(inviter))
	{
		sendMsg(clientFd, "You must be a channel operator to invite users to an invite-only channel\n");
		return;
	}
	channel->addInvite(invitee);
	sendMsg(invitee->getFd(), "You have been invited to " + channelName + " by " + inviter->getNickname() + "\n");
	sendMsg(clientFd, "Invitation sent to " + invitee->getNickname() + "\n");
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
	Client *client = getClientFd(clientFd);
	if (!client)
	{
		std::cerr << "Error: Client not found for fd " << clientFd << std::endl;
		return;
	}
	if (channels.count(channelName))
	{
		channel = channels[channelName];
	}
	else
	{
		channel = new Channel(channelName);
		channels[channelName] = channel;
		std::cout << "New channel has been created: " << channelName << std::endl;
		if (channel->addOperator(client))
		{
			sendMsg(clientFd, "You are already the operator of this channel\n");
		}
		else
		{
			sendMsg(clientFd, "You are now operator of the channel " + channelName + "\n");
		}
	}
	if (channel->isMember(client))
	{
		sendMsg(clientFd, "You are already in channel " + channelName + "\n");
		return;
	}
	if (channel->isInviteOnly() && !channel->isInvited(client))
	{
		sendMsg(clientFd, "This channel is invite-only. You need an invitation.\n");
		return;
	}
	channel->removeInvite(client);
	if (channel->getUserLimit() <= static_cast<int>(channel->getMembers().size()))
	{
		sendMsg(clientFd, "This channel is already full\n");
		return ;
	}
	//if (!channel->getChannelKey().empty())
	//{
	//	if ((tokens[3].empty() || ((channel->getChannelKey())[0] != '\0')) && tokens.size() > 4)
	//	{
	//		sendMsg(clientFd, "Key is required to join this channel!\n");
	//		return ;
	//	}
	//}
	if (channel->getKey())
	{
		if (tokens[3].empty() && tokens.size() != 3)
		{
			sendMsg(clientFd, "Key is required to join this channel!\n");
			return ;
		}
		if (tokens[3] != channel->getChannelKey())
		{
			sendMsg(clientFd, "The key is wrong!\n");
			return;
		}
	}
	if (channel->addClient(client))
	{
		sendMsg(clientFd, "You are already member of the channel " + channelName + "\n");
		return ;
	}
	else
	{
		sendMsg(clientFd, "You are now member of the channel " + channelName + "\n");
	}
	if (channel->getTopic().empty())
	{
		sendMsg(clientFd, "This channel has no topic yet\n");
	}
	else
	{
		sendMsg(clientFd, "Topic of this channel is:\n" + channel->getTopic() + "\n");
	}
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

void	Server::handleNotice(int clientFd, std::vector<std::string> &tokens)
{
	Channel	*channel = getChannel(tokens[1]);
	if (tokens.size() < 3 || tokens[1][0] != '#')
	{
		sendMsg(clientFd, "PRIVMSG requires arguments: <nickname/#channel> <message>\n");
		return;
	}
	if (!channel->isMember(getClientFd(clientFd)))
	{
		sendMsg(clientFd, "You must be a member of the channel to send a notice.\n");
		return;
	}
	if (channel)
	{
		std::vector<Client*> members = channel->getMembers();
		for (std::vector<Client*>::const_iterator it = members.begin(); it != members.end(); ++it)
		{
			Client *member = *it;
			int memberFd = member->getFd();
			Client *senderFd = getClientFd(clientFd);
			std::string senderNickname = senderFd->getNickname();
			std::string concatenatedMessage = senderNickname;
			concatenatedMessage += tokens[1];
			concatenatedMessage += " ";
			concatenatedMessage += tokens[2];
			concatenatedMessage += "\n";
			sendMsg(memberFd, concatenatedMessage);
		}
		return;
	}
	sendMsg(clientFd, "Channel must exist, in order to send message to it!\n");
}

void	Server::handlePrivmsg(int clientFd, std::vector<std::string> &tokens)
{
	if (tokens.size() < 3)
	{
		sendMsg(clientFd, "PRIVMSG requires arguments: <nickname/#channel> <message>!\n");
		return;
	}
	if (tokens[1][0] == '#')
	{
		sendMsg(clientFd, "PRIVMSG cannot be used on a channel!\n");
		return;
	}
	Client *receiverClient = getClient(tokens[1]);
	if (!receiverClient)
	{
		sendMsg(clientFd, "Nickname not found\n");
		return;
	}
	int	receiverFd = receiverClient->getFd();
	if (receiverFd == clientFd)
	{
		sendMsg(clientFd, "You cannot send message to yourself!\n");
		return;
	}
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
		if (secondsSinceLastChange < 7 * 24 * 60 * 60)
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
