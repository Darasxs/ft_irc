/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:38:09 by paprzyby          #+#    #+#             */
/*   Updated: 2025/06/21 17:35:38 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_HPP
# define COLORS_HPP

# include <iostream>

constexpr std::string_view RED		= "\033[0;31m";
constexpr std::string_view GREEN	= "\033[0;32m";
constexpr std::string_view YELLOW	= "\033[0;33m";
constexpr std::string_view BOLD		= "\033[1;37m";

constexpr std::string_view RESET	= "\033[0m";

#endif
