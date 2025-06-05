#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>

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
	std::string getTopic(void) const;
	void addClient(const Client &client);
	void removeClient(const Client &client);
	void addOperator(const Client &client);
	void removeOperator(const Client &client);

};

#endif;