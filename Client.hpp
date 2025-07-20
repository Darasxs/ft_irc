/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:01:25 by paprzyby          #+#    #+#             */
/*   Updated: 2025/07/20 11:40:33 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <vector>

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
		std::string					gethostname(void);
		std::string					getNickname(void);
		//other variables getters??

		//Setters:
		void 						setFd(int clientFd);
		void						set_ip_address(std::string ip_address);
		void						setNickname(std::string &nickname);
		void						sethostname(char *hostname);
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
		std::string					hostname;
		std::string					ip_address;
		int							clientFd;
		bool						isOperator;
		char						buffer[1024];
};

#endif
