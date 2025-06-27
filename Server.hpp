/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:03:27 by paprzyby          #+#    #+#             */
/*   Updated: 2025/06/27 18:25:11 by dpaluszk         ###   ########.fr       */
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
# include "colors.hpp"

# define PORT_NUMBER 6667

class Server
{
	public:
		Server();
		Server(const Server &other);
		Server &operator=(const Server &other);
		~Server();

		void		serverInitialization();
		void		serverStart();
		void		acceptClients();
		void		handleData(size_t &i);
		void		addClient(Client *client);
		void		removeClient(Client *client);
		Client*		getClient(const std::string &nickname);

		void		createChannel(const std::string &channelName);
		void		deleteChannel(const std::string &channelName);
		Channel		*getChannel(const std::string &channelName);

		void		setPassword(const std::string &password);
		std::string	getPassword();

		void parseData(int fd, Client &client, const std::vector<std::string> &tokens);
		std::vector<std::string> splitBuffer(const std::string &buffer);

		int handleKick(int clientFd, const std::vector<std::string> &tokens);

	private:
		int								serverFd;
		std::string 					hostName;
		std::map<int, Client>			clients;
		std::map<std::string, Channel*>	channels;
		bool							isRunning;
		std::string						password;
		std::vector<pollfd>				fds;
};

#endif
