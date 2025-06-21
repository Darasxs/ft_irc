/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:25 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/06/21 15:27:01 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"

Server::Server() : serverFd(-1)
{
}

Server::Server(int serverFd) : serverFd(serverFd)
{
}

Server::Server(const Server &other)
{
	*this = other;
}

Server &Server::operator=(const Server &other)
{
	if (this != &other)
	{
		this->portNumber = other.portNumber;
		this->serverFd = other.serverFd;
		this->clients = other.clients;
	}
	return (*this);
}

Server::~Server()
{
}

void Server::serverInitialization()
{
	int			opt;
	sockaddr_in	server_addr;

	serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverFd == -1)
		throw std::runtime_error("Failed to create socket");
	opt = 1;
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Failed to set socket options");
	std::memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(portNumber);
	if (bind(serverFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
		-1)
		throw std::runtime_error("Failed to bind socket");
	if (listen(serverFd, SOMAXCONN) == -1)
		throw std::runtime_error("Failed to listen on socket");
}

void Server::acceptClients()
{
	sockaddr_in	client_addr;
	socklen_t	client_len;
	int			clientFd;
	Client		newClient;
	pollfd		clientPollFd;

	std::cout << "Server is listening on port " << portNumber << std::endl;
	client_len = sizeof(client_addr);
	clientFd = accept(serverFd, (struct sockaddr *)&client_addr, &client_len);
	if (clientFd == -1)
	{
		std::cerr << "Failed to accept connection" << std::endl;
		return ;
	}
	newClient.setFd(clientFd);
	newClient.setIpAddress(inet_ntoa(client_addr.sin_addr));
	clients[clientFd] = newClient;	
	clientPollFd = {clientFd, POLLIN, 0};
	fds.push_back(clientPollFd);
	std::cout << "Client connected: " << inet_ntoa(client_addr.sin_addr) << std::endl;
}

void Server::parseData(int clientFd, const std::string &data)
{
	// parsing data here
}

void Server::handleData(size_t &i)
{
	char	buffer[1024];
	ssize_t	bytesRead;

	bytesRead = recv(fds[i].fd, buffer, sizeof(buffer) - 1, 0);
	if (bytesRead > 0)
	{
		buffer[bytesRead] = '\0';
		std::cout << "Received from client: " << buffer << std::endl;
		parseData(fds[i].fd, std::string(buffer));
	}
	else if (bytesRead == 0)
	{
		std::cout << "Client disconnected: " << fds[i].fd << std::endl;
		close(fds[i].fd);
		fds.erase(fds.begin() + i);
		i--;
	}
	else
	{
		std::cerr << "Error reading from client: " << fds[i].fd << " (" << strerror(errno) << ")" << std::endl;
		close(fds[i].fd);
		fds.erase(fds.begin() + i);
		i--;
	}
}

void Server::serverStart()
{
	pollfd	serverPollFd;
	int		pollReturn;

	serverPollFd = {serverFd, POLLIN, 0};
	fds.push_back(serverPollFd);
	while (true)
	{
		pollReturn = poll(fds.data(), fds.size(), -1);
		if (pollReturn == -1)
			throw std::runtime_error("poll failed");
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == serverFd)
				{
					acceptClients();
				}
				else
				{
					handleData(i);
				}
			}
		}
	}
}