#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>

class Server
{
  private:
	int portNumber;
	int serverFd;

  public:
	Server(void);
	Server(int serverFd);
	Server(const Server &other);
	Server &operator=(const Server &other);
	~Server(void);

	void serverInitialization(void);
};

#endif