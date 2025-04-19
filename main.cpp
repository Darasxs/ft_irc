/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:07:24 by dpaluszk          #+#    #+#             */
/*   Updated: 2025/04/19 16:50:10 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Irc.hpp"

int	main(int ac, char **av)
{
	if (ac < 3)
	{
		std::cerr << "Too few arguments passed." << std::endl;
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	else if (ac == 3)
	{
		(void)av;
		std::cout << "check" << std::endl;
		return (0);
	}
	else
	{
		std::cerr << "Too many arguments passed." << std::endl;
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
}
