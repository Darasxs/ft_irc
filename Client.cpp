/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:23 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/04/18 18:22:06 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void) : fd(-1), ipAddress("") {}

Client::Client(int fd, std::string &ipAddress) : fd(fd), ipAddress(ipAddress) {}

Client::Client(const Client &other)
{
	*this = other;
}

Client &Client::operator=(const Client &other)
{
	if(this != &other)
	{
		this->fd = other.fd;
		this->ipAddress = other.ipAddress;
	}
	return *this;
}

Client::~Client(void) {}