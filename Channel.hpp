/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:01:09 by paprzyby          #+#    #+#             */
/*   Updated: 2025/07/13 16:52:40 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <vector>
# include <algorithm>
# include "Client.hpp"

class Channel
{
  private:
	std::string name;
	std::string topic;
	std::vector<Client*> members;
	std::vector<Client*> operators;
  public:
	Channel(void);
	Channel(const std::string &name);
	Channel(const Channel &other);
	Channel &operator=(const Channel &other);
	~Channel(void);

	std::string getTopic(void) const;
	std::string getName(void) const;
	void setTopic(const std::string &topic);

	void addClient(Client *client);
	void removeClient(Client *client);
	bool isMember(Client *client) const;

	bool isOperator(Client *client) const;
	void addOperator(Client *client);
	void removeOperator(Client *client);

	void sendMessage(const std::string &message, Client *sender);

	std::vector<Client*> getMembers(void) const;
	std::vector<Client*> getOperators(void) const;

	bool hasMember(const Client &client) const;
	void removeMember(const Client &client);
	void addMember(Client *client);
};

#endif
