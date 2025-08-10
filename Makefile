# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 16:15:27 by paprzyby          #+#    #+#              #
#    Updated: 2025/08/10 16:50:13 by paprzyby         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME =		ircserv

SRC =		main.cpp \
			Irc.cpp \
			Server.cpp \
			Client.cpp \
			Channel.cpp \
			handleCommands.cpp

OBJ_DIR =	obj
OBJ =		$(SRC:%.cpp=$(OBJ_DIR)/%.o)

CC =		c++

RM =		rm -r

RM_DIR =	rm -rf

FLAGS =		-Wall -Wextra -Werror -std=c++17

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m
CLEAR_LINE = \033[2K\r
TICK = ✅

define PROGRESS_BAR
	@printf "";
	@for i in $$(seq 1 50); do \
		printf "▓"; \
	done
	@printf " 100%% \n"
endef

$(NAME): $(OBJ)
	@echo "======================================================="
	@echo "Building the executable..."
	@$(PROGRESS_BAR)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@if [ -f $(NAME) ] ; then \
		echo "\n$(CLEAR_LINE)$(GREEN)Compiled successfully!$(NC) $(TICK)\n"; \
		echo "run with: ./$(NAME)"; \
	else \
		echo "\n$(CLEAR_LINE)$(RED)$(NAME) failed to compile$(NC)"; \
	fi
	@echo "======================================================="

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	@if [ -d $(OBJ_DIR) ] ; then \
		$(RM_DIR) $(OBJ_DIR); \
		echo "\n$(RED)Object files removed$(NC)\n"; \
	else \
		echo "\n$(YELLOW)$(NAME) object files not found$(NC)\n"; \
	fi

fclean:
	@if [ -d $(OBJ_DIR) ] ; then \
		$(RM_DIR) $(OBJ_DIR); \
		echo "$(RED)$(NAME) object files removed$(NC)"; \
	fi
	@if [ -f $(NAME) ] ; then \
		$(RM) $(NAME); \
		echo "$(RED)$(NAME) removed$(NC)"; \
	else \
		echo "\n$(YELLOW)$(NAME) not found$(NC)\n"; \
	fi

re:		fclean all

.PHONY: all clean fclean re
