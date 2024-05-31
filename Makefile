# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 10:55:12 by aherbin           #+#    #+#              #
#    Updated: 2024/05/31 11:51:38 by aherbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 variables                                    #
# **************************************************************************** #

NAME = so_long

CC = cc

CCFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iinclude -IMLX42/include -Ilibft/include

LIBFT = libft/libft.a

CC_LINKER = -Llibft -lft -LMLX42 -lmlx42 -ldl -lglfw -lm -lpthread

RM = rm -f

MKDIR_P = mkdir -p

CYAN = \033[1;36m
GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[0;34m

C_FILES = so_long utils map_tools flood_fill

SRC_DIR = src/

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(C_FILES)))

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	$(CC) -g $(SRC) $(CCFLAGS) $(INCLUDES) $(CC_LINKER) -o $(NAME)
	@echo "$(GREEN)$@ $(BLUE)successfully compiled"

$(LIBFT):
	make -C libft

clean:
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) $(BLUE)successfully deleted"

fclean: clean
	make fclean -C libft
#	@$(RM) $(NAME)
#	@echo "$(RED)$(NAME) $(BLUE)successfully deleted"

re: fclean all

.PHONY: all clean fclean re
