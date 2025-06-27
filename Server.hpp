/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:03:27 by paprzyby          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/24 21:20:29 by dpaluszk         ###   ########.fr       */
=======
/*   Updated: 2025/06/21 17:56:00 by paprzyby         ###   ########.fr       */
>>>>>>> f5b77e54e2a6f0d8fe10842fa873edcf532c910e
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

		void parseData(int fd, const std::vector<std::string> &tokens);
		std::vector<std::string> splitBuffer(const std::string &buffer);

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
