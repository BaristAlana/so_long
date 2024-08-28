# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 10:55:12 by aherbin           #+#    #+#              #
#    Updated: 2024/08/28 11:45:54 by aherbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 variables                                    #
# **************************************************************************** #

NAME = so_long

CC = cc

CCFLAGS = -Wall -Wextra -Werror

INCLUDES = -I ./include -I ./$(MLX42)/include -I ./$(LIBFT)/include

#LIBFT = libft/libft.a

#CC_LINKER = -Llibft -lft -LMLX42 -lmlx42 -ldl -lglfw -lm -lpthread

LIBFT	:= ./lib/libft

LIBMLX	:= ./lib/MLX42

LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

RM = rm -rf

MKDIR_P = mkdir -p

CYAN = \033[1;36m
GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[0;34m

C_FILES = so_long utils map_tools flood_fill window movement score win_utils

SRC_DIR = src/

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(C_FILES)))

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: submodules libft libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(SRC)
	$(CC) -g $(SRC) $(CCFLAGS) $(INCLUDES) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$@ $(BLUE)successfully compiled"

libft:
	make -C $(LIBFT)

clean:
	@$(RM) $(LIBMLX)/build
	@make fclean -C $(LIBFT)
	@echo "$(BLUE)Compiled objects and dependencies successfully deleted"

fclean: clean
	@rm $(NAME)
	@echo "\n$(RED)$(NAME) $(BLUE)successfully deleted"

re: fclean all

submodules:
	@if git submodule status | egrep -q '^[-+]' ; then \
		echo "INFO: Need to reinitialize git submodules"; \
			git submodule update --init; \
	fi

.PHONY: all clean fclean re libmlx submodules

