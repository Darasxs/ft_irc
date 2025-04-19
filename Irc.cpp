/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:54:41 by paprzyby          #+#    #+#             */
/*   Updated: 2025/04/19 17:14:39 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

Irc::Irc()	{}

Irc::Irc(std::string input_port, std::string input_password)
{
	this->input_port = input_port;
	this->input_password = input_password;
	//
	std::cout << this->input_port << std::endl;
	std::cout << this->input_password << std::endl;
}

Irc::Irc(const Irc &other)
{
	*this = other;
}

Irc &Irc::operator=(const Irc &other)
{
	(void)other;
	//if(this != &other)
	//{

	//}
	return (*this);
}

Irc::~Irc()	{}
