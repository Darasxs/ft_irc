/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:23 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/07/25 16:22:30 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void) : nickname(""), hostname(nullptr), ip_address(""), clientFd(-1), isOperator(false), lastNicknameChange(0) {}

Client::Client(const Client &other)
{
	(void)other;
	//not finished
}

Client &Client::operator=(const Client &other)
{
	if (this != &other)
	{
		this->clientFd = other.clientFd;
		this->nickname = other.nickname;
		this->hostname = other.hostname;
		this->ip_address = other.ip_address;
		this->isOperator = other.isOperator;
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