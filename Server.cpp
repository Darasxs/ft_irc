/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:25 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/07/20 11:27:32 by paprzyby         ###   ########.fr       */
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

void Server::acceptClients()
{
	Client						*newClient = new Client();
	sockaddr_in					client_addr;
	socklen_t					client_len;
	pollfd						clientPollFd;
	int							client_fd;

	client_len = sizeof(client_addr);
	client_fd = accept(serverFd, (struct sockaddr *)&client_addr, &client_len);
	if (client_fd == -1)
	{
		std::cerr << "Failed to accept connection" << std::endl;
		return ;
	}
	newClient->setFd(client_fd);
	newClient->set_ip_address(inet_ntoa(client_addr.sin_addr));
	char host[NI_MAXHOST];
	if (getnameinfo((struct sockaddr *)&client_addr, client_len, host, sizeof(host), nullptr, 0, 0) == -1)
	{
		newClient->sethostname(host);
	}
	else
	{
		std::cerr << "Failed to retrieve hostname" << std::endl;
	}
	clients[client_fd] = newClient;
	clientPollFd = {client_fd, POLLIN, 0};
	fds.push_back(clientPollFd);
	std::cout << GREEN;
	std::cout << "New client connection from " << inet_ntoa(client_addr.sin_addr) << std::endl;
	std::cout << RESET;
}

void Server::sendPrivMsg(int clientFd, const std::string &message)
{
	if (message.empty())
		return;

	ssize_t bytesSent = send(clientFd, message.c_str(), message.size(), 0);
	if (bytesSent == -1)
	{
		std::cerr << "Failed to send prv msg: " << strerror(errno) << std::endl;
	}
	else if (static_cast<size_t>(bytesSent) < message.size())
	{
		std::cerr << "Partial message sent, only " << bytesSent << " bytes sent." << std::endl;
	}
	else
	{
		std::cout << "Message sent successfully to client " << clientFd << std::endl;
	}

}

void Server::parseData(int clientFd, Client *clients, std::vector<std::string> &tokens)
{
	if (tokens.empty())
		return;

	Client &client = clients[clientFd];

	(void)client;

	if(tokens[0] == "KICK")
	{
		//if(!handleKick(clientFd, clients, tokens))
		//	return;
		std::cout << "KICK command would be executed" << std::endl;
	}
	else if(tokens[0] == "INVITE")
	{
		std::cout << "INVITE command would be executed" << std::endl;
	}
	else if(tokens[0] == "")
	{
		std::cout << "No command" << std::endl;
	}
}

void Server::handleData(size_t &i)
{
	Client	*client = clients[fds[i].fd];
	char*	buffer = client->getBuffer();
	ssize_t bytesRead;

	bytesRead = recv(fds[i].fd, buffer, sizeof(buffer) - 1, 0);
	if (bytesRead > 0)
	{
		buffer[bytesRead] = '\0';
		if (buffer[0] == '\n')
			return ;
		//std::cout << buffer; //uncomment for testing
		std::vector<std::string> newBuffer = splitBuffer(buffer);
		parseData(fds[i].fd, client, newBuffer);
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
	Client	client;

	serverPollFd = {serverFd, POLLIN, 0};
	fds.push_back(serverPollFd);
	while (true)
	{
		if (poll(fds.data(), fds.size(), -1) == -1)
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

Channel *Server::getChannel(const std::string name)
{
	std::map<std::string, Channel*>::iterator it = channels.find(name);

	if (it != channels.end())
	{
		return it->second;
	}
	std::cerr << "Channel with name '" << name << "' not found." << std::endl;
	return nullptr;
}

