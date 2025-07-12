/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleCommands.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:33:04 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/07/12 12:50:47 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

void Server::parseData(int clientFd, const std::vector<std::string> &tokens)
{
	if (tokens.empty())
		return;

	Client &client = clients[clientFd];

	if(tokens[0] == "KICK")
	{
		//if(!handleKick(clientFd, client, tokens))
			//return;
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
