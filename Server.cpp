/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:25 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/07/24 12:24:49 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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

std::vector<std::string> Server::splitBuffer(const char *buffer)
{
	std::vector<std::string> tokens;
	std::istringstream stream(buffer);
	std::string word;

	while (stream >> word)
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
	if (getnameinfo((struct sockaddr *)&client_addr, client_len, host, sizeof(host), nullptr, 0, 0) == 0)
	{
		newClient->sethostname(host);
		//std::cout << newClient->gethostname() << std::endl;
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
	sendMsg(client_fd, "\nUse HELP command if you don't know howt to proceed.\n\n");
}

void Server::sendMsg(int receiverFd, const std::string &message)
{
	if (message.empty())
		return;
	ssize_t bytesSent = send(receiverFd, message.c_str(), message.size(), 0);

	if (bytesSent == -1)
	{
		std::cerr << "Failed to send msg: " << strerror(errno) << std::endl;
	}
	else if (static_cast<size_t>(bytesSent) < message.size())
	{
		std::cerr << "Partial message sent, only " << bytesSent << " bytes sent." << std::endl;
	}
}

void Server::sendPrivMsg(int receiverFd, int senderFd, const std::string &message)
{
	if (message.empty())
		return;
	Client *senderClient = getClientFd(senderFd);
	if (!senderClient)
	{
		std::cerr << "Sender client not found: " << senderFd << std::endl;
		return;
	}
	std::string formattedMessage = senderClient->getNickname() + ": " + message + "\n";
	ssize_t bytesSent = send(receiverFd, formattedMessage.c_str(), formattedMessage.size(), 0);

	if (bytesSent == -1)
	{
		std::cerr << "Failed to send prv msg: " << strerror(errno) << std::endl;
	}
	else if (static_cast<size_t>(bytesSent) < formattedMessage.size())
	{
		std::cerr << "Partial message sent, only " << bytesSent << " bytes sent." << std::endl;
	}
}

Client* Server::getClient(const std::string &nickname)
{
	for (std::map<int, Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second->getNickname() == nickname)
			return it->second;
	}
	return nullptr;
}

Client* Server::getClientFd(const int clientFd)
{
	for (std::map<int, Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second->getFd() == clientFd)
			return it->second;
	}
	return nullptr;
}

std::string Server::concatenateTokens(std::vector<std::string> &tokens)
{
	std::string	concatenatedTokens;
	for (size_t i = 2; i < tokens.size(); i++)
	{
		concatenatedTokens += tokens[i];
		concatenatedTokens += " ";
	}
	return concatenatedTokens;
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
	else if (tokens[0] == "PRIV")
	{
		if (tokens.size() < 3)
		{
			std::cerr << "PRIV requires arguments: <nickname> <message>" << std::endl;
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
		int	senderFd = senderClient->getFd();
		std::string message = concatenateTokens(tokens);
		sendPrivMsg(receiverFd, senderFd, message);
	}
	else if (tokens[0] == "NICK")
	{
		Client *targetClientFd = getClientFd(clientFd);
		if (!targetClientFd)
		{
			std::cerr << "Client's fd not found: " << targetClientFd << std::endl;
			return;
		}
		targetClientFd->setNickname(tokens[1]);
		//std::cout << targetClientFd->getNickname() << std::endl;
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

	bytesRead = recv(fds[i].fd, buffer, 1024, 0);
	if (bytesRead > 0)
	{
		buffer[bytesRead] = '\0';
		if (buffer[0] == '\n')
			return ;
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
