/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:54:41 by paprzyby          #+#    #+#             */
/*   Updated: 2025/06/01 17:17:57 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

Irc::Irc()	{}

Irc::Irc(int input_port, std::string input_password)
{
	this->input_port = input_port;
	this->input_password = input_password;
}

Irc::Irc(const Irc &other)
{
	*this = other;
	//not finished
}

Irc &Irc::operator=(const Irc &other)
{
	(void)other;
	//if(this != &other)
	//{

	//}
	return (*this);
	//not finished
}

Irc::~Irc()
{
	//free memory?
	//not finished
}

void	Irc::input_validation()
{
	if (input_port != DEFAULT_PORT)
	{
		throw std::runtime_error("Error: port does not match the default port number 6667.");
	}
	else if (input_password.empty()) //add more password requirements?
	{
		throw std::runtime_error("Error: invalid password.");
	}
}
