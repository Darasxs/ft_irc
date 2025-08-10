/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:54:41 by paprzyby          #+#    #+#             */
/*   Updated: 2025/08/10 17:20:15 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

Irc::Irc() : input_port(0), input_password("")	{}

Irc::Irc(int input_port, std::string input_password)
{
	this->input_port = input_port;
	this->input_password = input_password;
}

Irc::Irc(const Irc &other) : input_port(other.input_port), input_password(other.input_password)	{}

Irc &Irc::operator=(const Irc &other)
{
	if (this != &other)
	{
		this->input_port = other.input_port;
		this->input_password = other.input_password;
	}
	return (*this);
}

Irc::~Irc()	{}

void	Irc::input_validation()
{
	if (input_port != DEFAULT_PORT)
	{
		throw std::runtime_error("Error: port does not match the default port number 6667.");
	}
	else if (input_password.empty())
	{
		throw std::runtime_error("Error: invalid password.");
	}
}
