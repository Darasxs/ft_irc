/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:01:09 by paprzyby          #+#    #+#             */
/*   Updated: 2025/07/27 17:12:43 by paprzyby         ###   ########.fr       */
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
		std::string				name;
		std::string				topic;
		std::vector<Client*>	members;
		std::vector<Client*>	operators;
		std::vector<Client*>	invited;
		bool					inviteOnly;

	public:
		Channel(void);
		Channel(std::string name);
		Channel(const Channel &other);
		Channel &operator=(const Channel &other);
		~Channel(void);

		//Getters:
		std::string				getTopic(void) const;
		std::string				getName(void) const;
		std::vector<Client*>	getOperators(void) const;
		std::vector<Client*>	getMembers(void) const;

		//Setters:
		void		setTopic(const std::string &topic);
		//other varaibles setters??

		bool isMember(Client *client) const;
		bool isOperator(Client *client) const;
		void addClient(Client *client);
		void removeClient(Client *client);
		void addOperator(Client *client);
		void removeOperator(Client *client);
		bool hasMember(const Client &client) const;
		void removeMember(const Client &client);
		void sendMessage(const std::string &message, Client *sender);
		void addInvite(Client *invitee);
		bool isInvited(Client* invitee);
		bool isInviteOnly() const;
		void removeInvite(Client* client);
		void setInviteOnly(bool status);
};

#endif