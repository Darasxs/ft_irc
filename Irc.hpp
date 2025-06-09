/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:45:36 by paprzyby          #+#    #+#             */
/*   Updated: 2025/06/09 18:01:47 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <cstdlib>
# include <unistd.h>

# include "colors.hpp"
# include "Server.hpp"

# define DEFAULT_PORT 6667

class	Irc
{
	public:
		Irc();
		Irc(int input_port, std::string input_password);
		Irc(const Irc &other);
		Irc &operator=(const Irc &other);
		~Irc();

		void	input_validation();

	protected:
		int			input_port;
		std::string	input_password;
};

#endif
