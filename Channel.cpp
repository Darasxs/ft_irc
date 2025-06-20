/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:17:13 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/06/09 17:58:52 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void) : name(""), topic(""), members(), operators()
{
}

Channel::Channel(const std::string &name) : name(name), topic(""), members(),
	operators()
{
}

Channel &Channel::operator=(const Channel &other)
{
	if (this != &other)
	{
		this->name = other.name;
		this->topic = other.topic;
		this->members = other.members;
		this->operators = other.operators;
	}
	return (*this);
}

Channel::~Channel(void)
{
}

