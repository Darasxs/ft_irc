/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:23 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/06/21 15:33:27 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void) : clientFd(-1), nickname(""), realName(""), ipAddress(""),
	isOperator(false), channels()
{
}

Client::Client(const Client &other)
{
	*this = other;
}

Client &Client::operator=(const Client &other)
{
	if (this != &other)
	{
		this->clientFd = other.clientFd;
		this->nickname = other.nickname;
		this->realName = other.realName;
		this->ipAddress = other.ipAddress;
		this->isOperator = other.isOperator;
		this->channels = other.channels;
	}
	return (*this);
}

Client::~Client(void)
{
}

int Client::getFd(void)
{
	return (this->clientFd);
}

void Client::setFd(int clientFd)
{
	this->clientFd = clientFd;
}

void Client::setIpAddress(std::string ipAddress)
{
	this->ipAddress = ipAddress;
}

void Client::setNickname(std::string &nickname)
{
	this->nickname = nickname;
}

std::string Client::getNickname(void)
{
	return (this->nickname);
}

void Client::setRealName(std::string &realName)
{
	this->realName = realName;
}

std::string Client::getRealName(void)
{
	return (this->realName);
}

//void Client::setReceivedData(const std::string &data)
//{
//	receivedData = data;
//}

//std::string Client::getReceivedData() const
//{
//	return (receivedData);
//}
