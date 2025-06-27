/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:25 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/06/27 18:07:03 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

Server::Server()	{}

Server::Server(const Server &other)
{
	*this = other;
}

Server &Server::operator=(const Server &other)
{
	if (this != &other)
	{
		this->serverFd = other.serverFd;
		this->clients = other.clients;
	}
	return (*this);
}

Server::~Server()	{}

void Server::serverInitialization()
{
	int opt = 1;
	sockaddr_in server_addr;

	serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverFd == -1)
		throw std::runtime_error("Failed to create socket");
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Failed to set socket options");
	std::memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT_NUMBER);
	if (bind(serverFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		std::cerr << "Error: " << strerror(errno) << std::endl;
		throw std::runtime_error("Failed to bind socket");
	}
	if (listen(serverFd, SOMAXCONN) == -1)
		throw std::runtime_error("Failed to listen on socket");
	//if ( fcntl( _serverFD, F_SETFL, O_NONBLOCK ) < 0 )
	//	throw std::runtime_error( "Failed to set non-blocking mode" );
	//You can set or retrieve flags that control the behavior of a file descriptor, such as enabling non-blocking mode.
	std::cout << YELLOW;
	std::cout << "Listening on port " << PORT_NUMBER << "..." << std::endl;
	std::cout << RESET;
}

void Server::acceptClients()
{
	sockaddr_in	client_addr;
	socklen_t	client_len;
	Client		newClient;
	pollfd		clientPollFd;
	int			clientFd;

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
	std::cout << GREEN;
	std::cout << "New client connection from " << inet_ntoa(client_addr.sin_addr) << std::endl;
	std::cout << RESET;
}

std::vector<std::string> Server::splitBuffer(const std::string &buffer)
{
	std::vector<std::string> tokens;
	std::istringstream stream(buffer);
	std::string word;
	
	while(stream >> word)
	{
		tokens.push_back(word);
	}
	return tokens;
}

void Server::handleData(size_t &i)
{
	char	buffer[1024];
	ssize_t	bytesRead;
	Client	client;

	bytesRead = recv(fds[i].fd, buffer, sizeof(buffer) - 1, 0);
	if (bytesRead > 0)
	{
		buffer[bytesRead] = '\0';
		if (buffer[0] == '\n')
			return ;
		std::cout << buffer;
		std::vector newBuffer = splitBuffer(buffer);
		// LOOP FOR TESTING, BUT I THINK IT WILL ONLY WORK AFTER PROPERLY SENDING A MESSAGE
		//for (size_t word = 0; word < newBuffer.size(); word++)
		//{
		//	std::cout << newBuffer[word] << std::endl;
		//}
		parseData(fds[i].fd, split_buffer);
	}
	else if (bytesRead == 0)
	{
		std::cout << RED;
		std::cout << "Client disconnected..." << std::endl;
		std::cout << RESET;
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
			throw std::runtime_error("Error: poll failed");
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
