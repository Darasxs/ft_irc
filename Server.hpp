/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:03:27 by paprzyby          #+#    #+#             */
/*   Updated: 2025/07/26 16:07:33 by paprzyby         ###   ########.fr       */
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
# include <netdb.h>
# include <sstream>

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

		//Getters:
		Client*						getClient(const std::string &nickname);
		std::string					getPassword();

		//Setters:
		void						setPassword(const std::string &password);

		void						serverInitialization();
		void						serverStart();
		void						acceptClients();
		void						handleData(size_t &i);
		void						addClient(Client *client);
		void						removeClient(Client *client);
		void						createChannel(const std::string &channelName);
		void						deleteChannel(const std::string &channelName);
		void						parseData(int fd, Client *client, std::vector<std::string> &tokens);
		std::vector<std::string>	splitBuffer(const char *buffer);
		int							handleKick(int clientFd, const std::vector<std::string> &tokens);
		void						handleInvite(int clientFd, Client &client, const std::vector<std::string> &tokens);
		void						sendPrivMsg(int receiverFd, int senderFd, const std::string &message);
		void						sendMsg(int receiverfD, const std::string &message);
		Client*						getClientFd(const int clientFd);
		std::string					concatenateTokens(std::vector<std::string> &tokens);
		bool						checkNickname(std::string &nickname);

		//Commands:
		void						handleHelp(int clientFd);
		void						handleNick(int clientFd, std::vector<std::string> &tokens);
		void						handlePrivmsg(int clientFd, std::vector<std::string> &tokens);
		void						handleUser(int clientFd, std::vector<std::string> &tokens);
		void						handleJoin(int clientFd, std::vector<std::string> &tokens);
		void						handleChannelmsg(int clientFd, std::vector<std::string> &tokens);

	private:
		int								serverFd;
		std::map<int, Client*>			clients;
		std::map<std::string, Channel*>	channels;
		std::string						password;
		std::vector<pollfd>				fds;
};

#endif
