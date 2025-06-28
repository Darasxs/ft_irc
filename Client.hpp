/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:01:25 by paprzyby          #+#    #+#             */
/*   Updated: 2025/06/28 17:20:42 by paprzyby         ###   ########.fr       */
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

		int							getFd(void);
		void 						setFd(int clientFd);
		void						set_ip_address(std::string ip_address);
		void						setNickname(std::string &nickname);
		std::string					getNickname(void);
		void						sethostname(char *hostname);
		char						*gethostname(void);
		void						joinChannel(const std::string &channelName);
		void						leaveChannel(const std::string &channelName);
		std::vector<std::string>	getChannels(void);
		bool						isInChannel(const std::string &channelName);
		void						sendMessage(const std::string &message);
		void						operatorPromotion(void);
		void						operatorDemotion(void);
		void						parseData(int clientFd, const std::string &data);

	private:
		std::string					nickname;
		char						*hostname;
		std::string					ip_address;
		int							clientFd;
		bool						isOperator;
};

#endif
