/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:17:13 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/08/01 20:53:50 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void) : name(""), topic(""), members(), operators(), inviteOnly(false), lockedTopic(false), user_limit(INT_MAX)	{}
//client will set these variables only
//channel cannot be created without a name, topic, members, operators

Channel::Channel(std::string name) : name(name), topic(""), members(), operators(), inviteOnly(false), lockedTopic(false), user_limit(INT_MAX)	{}

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
		std::cerr << "Error: isMember() failed" << std::endl;
		return (true);
	}
	return std::find(members.begin(), members.end(), client) != members.end();
}

bool Channel::isOperator(Client *client) const
{
	if (client == nullptr)
	{
		std::cerr << "Error: isOperator() failed" << std::endl;
		return (true);
	}
	return std::find(operators.begin(), operators.end(), client) != operators.end();
}

bool Channel::addOperator(Client *client)
{
	if (client == nullptr)
	{
		std::cerr << "Error: addOperator() failed" << std::endl;
		return (true);
	}
	if (isOperator(client))
	{
		return (true);
	}
	operators.push_back(client);
	return (false);
}

bool Channel::addClient(Client *client)
{
	if (client == nullptr)
	{
		std::cerr << "Error: addClient() failed" << std::endl;
		return (true);
	}
	if (isMember(client))
	{
		return (true);
	}
	members.push_back(client);
	return (false);
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

void Channel::setTopicRestrictions(bool status)
{
	lockedTopic = status;
}

//void Channel::addOperator(Client *client)
//{
//	for (std::vector<Client*>::iterator it = operators.begin(); it != operators.end(); ++it)
//	{
//		if (*it == client)
//			return ;
//	}
//	operators.push_back(client);
//}

void Channel::removeMember(Client* client)
{
	std::vector<Client*>::iterator it = std::find(operators.begin(), operators.end(), client);
	if (it != operators.end())
	{
		operators.erase(it);
	}
}

void	Channel::removeClient(Client *client)
{
	std::vector<Client*>::iterator it = std::find(members.begin(), members.end(), client);
	if (it != members.end())
	{
		members.erase(it);
		removeMember(client);
		removeInvite(client);
	}
}

bool	Channel::isTopicLocked()
{
	return (this->lockedTopic);
}

void	Channel::setTopic(const std::string &topic)
{
	this->topic = topic;
}

std::string	Channel::getTopic(void) const
{
	return (this->topic);
}

void	Channel::setUserLimit(int limit)
{
	user_limit = limit;
}

int	Channel::getUserLimit(void)
{
	return (this->user_limit);
}
