/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:01:09 by paprzyby          #+#    #+#             */
/*   Updated: 2025/08/01 21:38:29 by paprzyby         ###   ########.fr       */
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
		bool					lockedTopic;
		int						user_limit;
		std::string				channel_key;
		bool					key;

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
		bool addClient(Client *client);
		void removeClient(Client *client);
		bool addOperator(Client *client);
		void removeOperator(Client *client);
		bool hasMember(const Client &client) const;
		void removeMember(Client* client);
		void sendMessage(const std::string &message, Client *sender);
		void addInvite(Client *invitee);
		bool isInvited(Client* invitee);
		bool isInviteOnly() const;
		void removeInvite(Client* client);
		void setInviteOnly(bool status);
		bool isTopicLocked();
		void setTopicRestrictions(bool status);
		void setOperatorPrivilege(bool status);
		void setUserLimit(int limit);
		int	getUserLimit(void);
		void setChannelKey(std::string key);
		std::string	getChannelKey();
		void setKey(bool key);
		bool getKey(void);
};

#endif