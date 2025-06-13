/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:25 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/06/13 17:47:05 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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
	//AF_INET == IPv4
	//SOCK_STREAM == TCP
	//0: Specifies the protocol (0 lets the system choose the default protocol for the given socket type, which is TCP for SOCK_STREAM)

	// Set socket options
	int opt = 1;
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Failed to set socket options");
	//setsockopt is a system call used to configure options for a socket.
	//SOL_SOCKET specifies that the option applies to the socket layer.
	//SO_REUSEADDR is the option being set.
	//&opt is a pointer to the value being set (in this case, 1 to enable the option).
	//sizeof(opt) specifies the size of the value.

	// Configure server address
	sockaddr_in server_addr;
	std::memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(portNumber);
	//sockaddr_in server_addr;
	//Declares a structure of type sockaddr_in, which is used to define an IPv4 address and port for the socket.
	//std::memset(&server_addr, 0, sizeof(server_addr));
	//Initializes the server_addr structure to zero to ensure no garbage values are present. This is important to avoid undefined behavior.
	//server_addr.sin_family = AF_INET;
	//Specifies the address family as AF_INET, which means the socket will use IPv4.
	//server_addr.sin_addr.s_addr = INADDR_ANY;
	//Sets the IP address to INADDR_ANY, which allows the server to accept connections on any network interface (e.g., localhost, Ethernet, Wi-Fi).
	//server_addr.sin_port = htons(portNumber);
	//Sets the port number for the server. The htons function converts the port number from host byte order to network byte order (big-endian), which is required for network communication.

	// Bind the socket to the port
	if (bind(serverFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		throw std::runtime_error("Failed to bind socket");
	//Purpose: The bind function associates the server socket (serverFd) with the specified IP address and port stored in the server_addr structure.
	//Why it's needed: Without binding, the socket would not be tied to a specific port or network interface, and the server would not know where to listen for incoming connections.
	//Error handling: If the bind call fails (e.g., the port is already in use or the process lacks permissions), an exception is thrown.

	// Start listening for incoming connections
	if (listen(serverFd, SOMAXCONN) == -1)
		throw std::runtime_error("Failed to listen on socket");
	//Purpose: The listen function puts the server socket into a passive mode, meaning it will wait for incoming connection requests from clients.
	//SOMAXCONN: This specifies the maximum number of pending connections that can be queued. SOMAXCONN is a system-defined constant representing the maximum value allowed.
	//Why it's needed: Without calling listen, the server cannot accept connections, as the socket would remain in an unconnected state.
	//Error handling: If the listen call fails (e.g., due to insufficient system resources), an exception is thrown.
}

void Server::serverStart()
	{
	sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);

	while (true)
	{
		// Accept a new client connection
		int clientFd = accept(serverFd, (struct sockaddr *)&client_addr, &client_len);
		if (clientFd == -1)
		{
			std::cerr << "Failed to accept connection" << std::endl;
			continue;
		}

		std::cout << "Client connected!" << std::endl;

		//nie wiem czy tutaj odcyztac ta wiadomosc i ja zapisac moze w strucie, 
		// a potem w innych funkcjach sparsowac i wyslac ta wiadomosc?
		
		//// Read a message from the client
		//char buffer[1024];
		//ssize_t bytesRead = read(clientFd, buffer, sizeof(buffer));
		//if (bytesRead > 0)
		//{
		//    std::cout << "Received: " << std::string(buffer, bytesRead) << std::endl;

		//    // Echo the message back to the client
		//    write(clientFd, buffer, bytesRead);
		//}

		//// Close the client connection
		//close(clientFd);
	}
}
