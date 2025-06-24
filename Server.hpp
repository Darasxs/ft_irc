/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:03:27 by paprzyby          #+#    #+#             */
/*   Updated: 2025/06/24 21:20:29 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <vector>
# include <map>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <poll.h>
# include <unistd.h>

# include "Client.hpp"
# include "Channel.hpp"

# define PORT_NUMBER 6667

class Server
{
	public:
		Server();
		Server(int serverFd);
		Server(const Server &other);
		Server &operator=(const Server &other);
		~Server();

		void		serverInitialization();
		void		serverStart();
		void		acceptClients();
		void		handleData(size_t &i);
		void		addClient(Client *client);
		void		removeClient(Client *client);
		Client*		getClient(const std::string &nickname); // identifying client by nickname, for example to send private message to him

		void		createChannel(const std::string &channelName);
		void		deleteChannel(const std::string &channelName);
		Channel*	getChannel(const std::string &channelName);// similar as getClient

		void		setPassword(const std::string &password);
		std::string	getPassword();

		void parseData(int fd, const std::vector<std::string> &tokens);
		std::vector<std::string> splitBuffer(const std::string &buffer);

	private:
		int								serverFd; // socket that listens for connections, binds to a specific port and accept conncections
		std::string 					hostName;
		std::map<int, Client>			clients;
		std::map<std::string, Channel*>	channels;
		bool							isRunning;
		std::string						password;
		std::vector<pollfd>				fds;
};

#endif
