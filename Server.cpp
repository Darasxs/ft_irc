/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:25 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/06/15 17:40:01 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"

Server::Server() : serverFd(-1) {}

Server::Server(int serverFd) : serverFd(serverFd) {}

Server::Server(const Server &other)
{
	*this = other;
}

Server &Server::operator=(const Server &other)
{
	if(this != &other)
	{
		this->portNumber = other.portNumber;
		this->serverFd = other.serverFd;
	}
	return (*this);
}

Server::~Server() {}

void	Server::serverInitialization()
{
	serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverFd == -1)
		throw std::runtime_error("Failed to create socket");

	int opt = 1;
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Failed to set socket options");

	sockaddr_in server_addr;
	std::memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(portNumber);

	if (bind(serverFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		throw std::runtime_error("Failed to bind socket");

	if (listen(serverFd, SOMAXCONN) == -1)
		throw std::runtime_error("Failed to listen on socket");
}

void Server::serverStart()
{
	sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	std::map<int, Client> clients;
	
	while (true)
	{
		int clientFd = accept(serverFd, (struct sockaddr *)&client_addr, &client_len);
		if (clientFd == -1)
		{
			// tu nie jestem pewien, ale chyba musi to byc jakos inaczej napisane
			// nie wiem czy nie czasami throw itp.
			std::cerr << "Failed to accept connection" << std::endl;
			continue;
		}
		
		Client newClient;
		newClient.setFd(clientFd);
		newClient.setIpAddress(inet_ntoa(client_addr.sin_addr));
		clients[clientFd] = newClient;
		std::cout << "Client connected!" << std::endl;

	}
}
