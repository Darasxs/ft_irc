#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client
{
	private:
		int fd;
		std::string ipAddress;
	public:
		Client(void);
		Client(int fd, std::string &ipAddress);
		Client(const Client &other);
		Client &operator=(const Client &other);
		~Client(void);

		int getFd(void);
		void setFd(int fd);
		void setIpAddress(std::string ipAddress);
};

#endif