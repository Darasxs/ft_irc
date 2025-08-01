/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:01:25 by paprzyby          #+#    #+#             */
/*   Updated: 2025/07/27 18:34:49 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <vector>
# include <ctime>

class Client
{
	public:
		Client(void);
		Client(const Client &other);
		Client &operator=(const Client &other);
		~Client(void);

		//Getters:
		int							getFd(void);
		char						*getBuffer();
		char						*gethostname(void);
		std::string					getNickname(void);
		std::string					getUsername(void);
		time_t						getLastNicknameChange(void);

		//Setters:
		void 						setFd(int clientFd);
		void						set_ip_address(std::string ip_address);
		void						setNickname(std::string &nickname);
		void						sethostname(char *hostname);
		void						setUsername(std::string &username);
		void						setLastNicknameChange(time_t nicknameChange);
		//other variables setters??

		void						joinChannel(const std::string &channelName);
		void						leaveChannel(const std::string &channelName);
		bool						isInChannel(const std::string &channelName);
		void						sendMessage(const std::string &message);
		void						operatorPromotion(void);
		void						operatorDemotion(void);
		void						parseData(int clientFd, const std::string &data);

	private:
		std::string					nickname;
		std::string					username;
		char						*hostname;
		std::string					ip_address;
		int							clientFd;
		bool						isOperator;
		char						buffer[1024];
		time_t						lastNicknameChange;
};

#endif
