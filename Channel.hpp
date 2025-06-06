#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <vector>
# include "Client.hpp"

class Channel
{
  private:
	std::string name;
	std::string topic;
	std::vector<Client> members;
	std::vector<Client> operators;
  public:
	// some function for sending message in the channel?
	Channel(void);
	Channel(const std::string &name);
	Channel(const Channel &other);
	Channel &operator=(const Channel &other);
	~Channel(void);

	std::string getTopic(void) const;
	std::string getName(void) const;
	void setTopic(const std::string &topic);

	void addClient(const Client &client);
	void removeClient(const Client &client);
	bool isMember(Client *client) const;

	void addOperator(const Client &client);
	void removeOperator(const Client &client);
	bool isOperator(Client *client) const;

	void broadcastMessage(const std::string &message, Client *sender);

};

#endif;