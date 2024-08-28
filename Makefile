# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 10:55:12 by aherbin           #+#    #+#              #
#    Updated: 2024/08/28 14:35:50 by aherbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 variables                                    #
# **************************************************************************** #

NAME := so_long
CC := cc
CCFLAGS := -Wall -Wextra -Werror
INCLUDES := -I ./include -I ./$(MLX42)/include -I ./$(LIBFT)/include
RM := rm -rf

CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[0;34m
CYAN 		:= \033[1;36m

#           SO_LONG           #

SRC := src/so_long.c src/utils.c src/map_tools.c src/flood_fill.c src/window.c src/movement.c src/score.c src/win_utils.c
BIN := bin
OBJS	= ${SRC:src/%c=${BIN}/%o}

#          DEPENDENCY         #

LIBFT		:= ./lib/libft
LIBFTAR 	:= $(LIBFT)/libft.a
LIBMLX		:= ./lib/MLX42
LIBMLXAR	:= $(LIBMLX)/build/libmlx42.a
LIBS		:= $(LIBFTAR) $(LIBMLXAR) -ldl -lglfw -pthread -lm

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(BIN) $(NAME)

${BIN}/%o: src/%c
	@${CC} -c $< ${CFLAGS} ${IFLAGS} -o $@

${BIN}:
	@mkdir -p ${BIN}

$(NAME): $(OBJS) | $(LIBMLXAR) $(LIBFTAR)
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
	@$(CC) ${OBJS} $(CCFLAGS) $(INCLUDES) $(LIBS) -o $(NAME)
	@echo "$(YELLOW)$(NAME)$(BLUE) compiled $(GREEN)✔️$(CLR_RMV)"

$(LIBFTAR):
	@make -C $(LIBFT) --no-print-directory

$(LIBMLXAR):
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 --no-print-directory

clean:
	@${RM} ${BIN}
	@echo "$(RED)OBJS $(BLUE)successfully deleted"

fclean: clean
	@make fclean -C $(LIBFT) --no-print-directory
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) $(BLUE)successfully deleted"

re: fclean all

.PHONY: all clean fclean re
