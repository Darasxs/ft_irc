/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:33:04 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/07/13 17:47:45 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void	Server::handleInvite(int clientFd, Client &client, const std::vector<std::string> &tokens)
{
	if(tokens.size() > 3 || tokens[1].empty() || tokens[2].empty())
	{
		std::cerr << "INVITE requires arguments: <nickname>, <channel>" << std::endl;
	}
	else if (std::find(clients.begin(), clients.end(), client) != clients.end())
	{
		std::cerr << "This operator client does not exist!" << std::endl;
	}
	else if (std::find(channels.begin(), channels.end(), tokens[2]) != channels.end())
	{
		std::cerr << "This channel does not exist!" << std::endl;
	}
	Channel *channel = getChannel(tokens[2]);
	if (!channel)
	{
		return;
	}
	if (std::find(clients.begin(), clients.end(), tokens[1]) != clients.end())
	{
		std::cerr << "The target client does not exist!" << std::endl;
	}
	if (!channel->isMember(&client) || !channel->isOperator(&client))
	{
		std::cerr << "To invite others to a channel, the client must be an operator of this channel!" << std::endl;
		return;
	}

	std::cout << "The target client has now become the member of the channel." << std::endl;
}

void Server::parseData(int clientFd, std::vector<std::string> &tokens)
{
	if (tokens.empty())
		return;

	Client &client = clients[clientFd];

	if(tokens[0] == "KICK")
	{
		if(!handleKick(clientFd, client, tokens))
			return;
	}
	else if(tokens[0] == "INVITE")
	{

	}
	else if(tokens[0] == "")
	{

	}
}

int Server::handleKick(int clientFd, Client &client, const std::vector<std::string> &tokens)
{
	if (!client.isOperator)
	{
		std::cerr << "Client " << clientFd << " is not an Operator." << std::endl;
		std::cerr << "ONLY OPERATORS CAN USE KICK!" << std::endl;
		return 0;
	}
	if(tokens[1].empty())
	{
		std::cerr << "KICK requires an argument!" << std::endl;
		return 0;
	}

	const std::string &targerNickname = tokens[1];


	else
	{
		if(tokens[1] == )
	}
}
