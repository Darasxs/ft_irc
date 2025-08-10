/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:23 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/08/10 17:03:59 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void) : nickname(""), username(""), hostname(nullptr), ip_address(""), clientFd(-1), isOperator(false), buffer(""), lastNicknameChange(0)	{}

Client::Client(const Client &other) : nickname(other.nickname), username(other.username), hostname(other.hostname), ip_address(other.ip_address), clientFd(other.clientFd), isOperator(other.isOperator), buffer(""), lastNicknameChange(other.lastNicknameChange)	{}

Client &Client::operator=(const Client &other)
{
	if (this != &other)
	{
		this->clientFd = other.clientFd;
		this->nickname = other.nickname;
		this->hostname = other.hostname;
		this->ip_address = other.ip_address;
		this->isOperator = other.isOperator;
		this->username = other.username;
		this->lastNicknameChange = other.lastNicknameChange;
	}
	return (*this);
}

Client::~Client(void)	{}

int Client::getFd(void)
{
	return (this->clientFd);
}

void Client::setFd(int clientFd)
{
	this->clientFd = clientFd;
}

void Client::set_ip_address(std::string ip_address)
{
	this->ip_address = ip_address;
}

void Client::setNickname(std::string &nickname)
{
	this->nickname = nickname;
}

std::string Client::getNickname(void)
{
	return (this->nickname);
}

void Client::setUsername(std::string &username)
{
	this->username = username;
}

std::string Client::getUsername(void)
{
	return (this->username);
}

void Client::sethostname(char *hostname)
{
	this->hostname = hostname;
}

char	*Client::gethostname(void)
{
	return (this->hostname);
}

char* Client::getBuffer()
{
	return buffer;
}

void	Client::setLastNicknameChange(time_t nicknameChange)
{
	this->lastNicknameChange = nicknameChange;
}

time_t	Client::getLastNicknameChange(void)
{
	return (this->lastNicknameChange);
}