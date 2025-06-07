/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:23 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/06/07 19:36:23 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void) : clientFd(-1), ipAddress("") {}

Client::Client(int clientFd, std::string &ipAddress) : clientFd(clientFd), ipAddress(ipAddress) {}

Client::Client(const Client &other)
{
	*this = other;
}

Client &Client::operator=(const Client &other)
{
	if(this != &other)
	{
		this->clientFd = other.clientFd;
		this->ipAddress = other.ipAddress;
	}
	return (*this);
}

Client::~Client(void) {}

int Client::getFd(void)
{
	return this->clientFd;
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
	return this->nickname;
}

