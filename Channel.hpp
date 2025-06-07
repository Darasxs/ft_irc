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

	void addOperator(Client *client);
	void removeOperator(Client *client);
	bool isOperator(Client *client) const;

	void sendMessage(const std::string &message, Client *sender);

	std::vector<Client*> getMembers(void) const;
	std::vector<Client*> getOperators(void) const;
};

#endif;