/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:17:13 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/07/27 17:13:37 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void) : name(""), topic(""), members(), operators(), inviteOnly(false)	{}
//client will set these variables only
//channel cannot be created without a name, topic, members, operators

Channel::Channel(std::string name) : name(name), topic(""), members(), operators(), inviteOnly(false)	{}

Channel::Channel(const Channel &other)
{
	(void)other;
	//not finished
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

Channel::~Channel(void)	{}

bool Channel::isMember(Client *client) const
{
	if (client == nullptr)
	{
		std::cerr << "error: nullptr" << std::endl;
		return (true);
	}
	return std::find(members.begin(), members.end(), client) != members.end();
}

bool Channel::isOperator(Client *client) const
{
	if (client == nullptr)
	{
		std::cerr << "error: nullptr" << std::endl;
		return (true);
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

std::string Channel::getName(void) const
{
	return (this->name);
}

std::vector<Client*> Channel::getMembers(void) const
{
	return this->members;
}

void Channel::addInvite(Client* invitee)
{
	for (std::vector<Client*>::iterator it = invited.begin(); it != invited.end(); ++it)
	{
		if (*it == invitee)
			return ;
	}
	invited.push_back(invitee);
}

bool Channel::isInvited(Client* invitee)
{
	for (std::vector<Client*>::const_iterator it = invited.begin(); it != invited.end(); ++it)
	{
		if (*it == invitee)
			return true;
	}
	return false;
}

bool Channel::isInviteOnly() const
{
	return inviteOnly;
}

void Channel::removeInvite(Client* client)
{
	for (std::vector<Client*>::iterator it = invited.begin(); it != invited.end(); ++it)
	{
		if (*it == client)
		{
			invited.erase(it);
			return;
		}
	}
}

void Channel::setInviteOnly(bool status)
{
	inviteOnly = status;
}
