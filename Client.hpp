/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:01:25 by paprzyby          #+#    #+#             */
/*   Updated: 2025/06/27 17:27:37 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <vector>
class Client
{
  private:
	int clientFd; // the socket for individual connections to the server
	std::string nickname;
	std::string realName;
	std::string ipAddress;
	bool isOperator;
	std::vector<std::string> channels; // which channels is each client a part of
	std::string						receivedData;

  public:
	Client(void);
	Client(const Client &other);
	Client &operator=(const Client &other);
	~Client(void);

	int getFd(void);
	void setFd(int clientFd);

	void setIpAddress(std::string ipAddress);

	void setNickname(std::string &nickname);
	std::string getNickname(void);

	void setRealName(std::string &realName);
	std::string getRealName(void);

	void joinChannel(const std::string &channelName);
	void leaveChannel(const std::string &channelName);
	std::vector<std::string> getChannels(void);
	bool isInChannel(const std::string &channelName);

	void sendMessage(const std::string &message);

	void operatorPromotion(void);
	void operatorDemotion(void);

	void 		parseData(int clientFd, const std::string &data);
};

#endif
