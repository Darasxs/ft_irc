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

};

#endif;