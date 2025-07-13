/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:17:13 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/07/13 16:27:43 by paprzyby         ###   ########.fr       */
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

bool Channel::isMember(Client *client) const
{
	if (client == nullptr)
	{
		std::cerr << "error: nullptr" << std::endl;
		return ;
	}

	return std::find(members.begin(), members.end(), client) != members.end();
}

bool Channel::isOperator(Client *client) const
{
	if (client == nullptr)
	{
		std::cerr << "error: nullptr" << std::endl;
		return ;
	}
	return std::find(operators.begin(), operators.end(), client) != operators.end();
}

void Channel::addOperator(Client *client)
{
	if (client == nullptr)
	{
		std::cerr << "error: nullptr" << std::endl;
		return ;
	}

	if (isOperator(client))
	{
		std::cerr << "The client is already an operator." << std::endl;
		return ;
	}

	operators.push_back(client);
	std::cout << "The client has become na operator." << std::endl;
}

void Channel::addClient(Client *client)
{
	if (client == nullptr)
	{
		std::cerr << "error: nullptr" << std::endl;
		return ;
	}

	if (isMember(client))
	{
		std::cerr << "The client is already a member of this channel." << std::endl;
		return ;
	}

	members.push_back(client);
	std::cout << "The client has been added to the channel." << std::endl;
}
