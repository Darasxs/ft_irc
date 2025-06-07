#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <vector>
# include <map>
# include "Client.hpp"
# include "Channel.hpp"

class Server
{
  private:
	int portNumber;
	int serverFd; // socket that listens for connections, binds to a specific port and accept conncections
	std::string hostName;
	std::vector<Client*> clients;
	std::map<std::string, Channel*> channels;
	bool isRunning;
	std::string password;

  public:
	Server(void);
	Server(int serverFd);
	Server(const Server &other);
	Server &operator=(const Server &other);
	~Server(void);

	void addClient(Client *client);
	void removeClient(Client *client);
	Client* getClient(const std::string &nickname) const; // identifying client by nickname, for example to send private message to him

	void createChannel(const std::string &channelName);
	void deleteChannel(const std::string &channelName);
	Channel* getChannel(const std::string &channelName) const; // similar as getClient

	void	serverInitialization(void);
	void	setPassword(const std::string &password);
	std::string	getPassword() const;
	// bool checkPassword(const std::string &password) const; - to check if the password is correct?
};

#endif