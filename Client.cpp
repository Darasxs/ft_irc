/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:23 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/06/21 16:09:49 by dpaluszk         ###   ########.fr       */
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

//void Client::parseData(int clientFd, const std::string &data)
//{
//	Client &client = clients[clientFd];

//	if (data.find("KICK") != std::string::npos)
//	{
//		if (!client.isOperator)
//		{
//			handleKick
//		}
//	}
//}