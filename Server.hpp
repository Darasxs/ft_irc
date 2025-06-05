#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <vector>
# include <map>
class Server
{
  private:
	int portNumber;
	int serverFd; // socket that listens for connections, binds to a specific port and accept conncections
	std::string hostName;
	std::vector<Client> clients;
	std::map<std::string, Channel> channels;
	bool isRunning;
	std::string password;

  public:
	Server(void);
	Server(int serverFd);
	Server(const Server &other);
	Server &operator=(const Server &other);
	~Server(void);

	void	serverInitialization(void);
	void	setPassword(const std::string &password);
	std::string	getPassword() const;
	// bool checkPassword(const std::string &password) const; - to check if the password is correct?
};

#endif