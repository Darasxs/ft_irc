/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:24 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/06/01 17:37:03 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

int	main(int ac, char **av)
{
	if (ac < 3)
	{
		std::cout << RED;
		std::cerr << "Too few arguments passed." << std::endl;
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		std::cout << RESET;
		return (1);
	}
	else if (ac == 3)
	{
		try
		{
			Irc	irc = Irc(std::atoi(av[1]), av[2]);
			irc.input_validation();
			system("clear");
			std::cout << GREEN;
			std::cout << "===============================================================" << std::endl;
			std::cout << "===========  IRC Server created by Pawel and Darek  ===========" << std::endl;
			std::cout << "================================================================" << std::endl;
			sleep(1);
			std::cout << YELLOW;
			std::cout << "Server is starting..." << std::endl;
			std::cout << "Listening on port: " << av[1] << std::endl;
			std::cout << RESET;
			//main logic here
			while (1)	{}
		}
		catch(const std::exception& e)
		{
			std::cout << RED;
			std::cerr << e.what() << std::endl;
			std::cout << RESET;
			return (1);
		}
		return (0);
	}
	else
	{
		std::cout << RED;
		std::cerr << "Too many arguments passed." << std::endl;
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		std::cout << RESET;
		return (1);
	}
}
