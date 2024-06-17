# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 19:28:23 by dmodrzej          #+#    #+#              #
#    Updated: 2024/06/17 19:40:28 by dmodrzej         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

# compiler
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror

# sources
SRC_DIR =	srcs/
SRC		=	main.c philo.c utils.c \
			# init.c threads.c \
			# actions.c monitor.c print.c
SRCS	=	$(addprefix $(SRC_DIR), $(SRC))

# objects
OBJ_DIR	=	objs/
OBJ		=	$(SRC:.c=.o)
OBJS	=	$(addprefix $(OBJ_DIR), $(OBJ))

# includes
INC		=	-I includes/

# colors & symbols
GREEN 	= 	\033[0;32m
CYAN	=	\033[0;36m
NC		= 	\033[0m
TICK	=	✅

define PRINT_LOADING
	@printf "$(CYAN)["
	@for i in $$(seq 0 10 100); do \
		printf "▓"; \
		sleep 0.1; \
	done
	@printf "] 100%%$(RESET)\n"
endef

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
			@$(CC) $(FLAGS) -c $< -o $@ $(INC)

all:		$(NAME)

$(NAME):	$(OBJS)
			@echo "$(CYAN)Compiling program...$(NC)"
			@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INC)
			@$(PRINT_LOADING)
			@echo "$(GREEN)Program compilation successful		$(TICK)$(NC)"

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)

clean:		
			@echo "$(CYAN)Cleaning .o files...$(NC)"
			@rm -rf $(OBJ_DIR)
			@$(PRINT_LOADING)
			@echo "$(GREEN)Cleaning of of .o files successful	$(TICK)$(NC)"

fclean:		clean
			@echo "$(CYAN)Cleaning program...$(NC)"
			@rm -f $(NAME)
			@$(PRINT_LOADING)
			@echo "$(GREEN)Full cleaning successful		$(TICK)$(NC)"

re:			fclean all

.PHONY:		all clean fclean re