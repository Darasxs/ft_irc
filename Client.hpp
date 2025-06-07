#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <vector>
class Client
{
  private:
	int clientFd; // the socket for individual connections to the server
	std::string nickname;
	std::string realName;
	std::string ipAddress;
	bool isOperator;
	std::vector<std::string> channels; // which channels is each client a part of

  public:
	Client(void);
	Client(int clientFd, std::string &ipAddress);
	Client(const Client &other);
	Client &operator=(const Client &other);
	~Client(void);

	int getFd(void);
	void setFd(int clientFd);
	void setIpAddress(std::string ipAddress);

	std::string getNickname(void) const;
	void setNickname(const std::string &nickname);

	std::string getRealName(void) const;
	void setRealName(const std::string &realName);

	void joinChannel(const std::string &channelName);
	void leaveChannel(const std::string &channelName);
	std::vector<std::string> getChannels(void) const;
	bool isInChannel(const std::string &channelName) const;

	void sendMessage(const std::string &message) const;

	void operatorPromotion(void);
	void operatorDemotion(void);
};

#endif