/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:45:36 by paprzyby          #+#    #+#             */
/*   Updated: 2025/04/19 17:23:08 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>

# define PORT 6666
# define PASSWORD 123

class	Irc
{
	public:
		Irc();
		Irc(std::string input_port, std::string input_password);
		Irc(const Irc &other);
		Irc &operator=(const Irc &other);
		~Irc();

		void	input_validation(const Irc &irc);

	private:
		std::string	input_port;
		std::string	input_password;
};

#endif
