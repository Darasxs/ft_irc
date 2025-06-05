#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class Client
{
  private:
	int clientFd; // the socket for individual connections to the server
	std::string ipAddress;

  public:
	Client(void);
	Client(int clientFd, std::string &ipAddress);
	Client(const Client &other);
	Client &operator=(const Client &other);
	~Client(void);

	int getFd(void);
	void setFd(int clientFd);
	void setIpAddress(std::string ipAddress);
};

#endif