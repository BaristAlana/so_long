# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 10:55:12 by aherbin           #+#    #+#              #
#    Updated: 2024/08/28 11:48:58 by aherbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 variables                                    #
# **************************************************************************** #

NAME := so_long
CC := cc
CCFLAGS := -Wall -Wextra -Werror
INCLUDES := -I ./include -I ./$(MLX42)/include -I ./$(LIBFT)/include
LIBFT	:= ./lib/libft
LIBMLX	:= ./lib/MLX42
LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
RM := rm -rf
BIN := bin
#C_FILES := so_long utils map_tools flood_fill window movement score win_utils
SRC := src/so_long.c src/utils.c src/map_tools.c src/flood_fill.c src/window.c src/movement.c src/score.c src/win_utils.c
#SRC_DIR := src/
#SRC := $(addprefix $(SRC_DIR), $(addsuffix .c, $(C_FILES)))
OBJS	= ${SRC:src/%c=${BIN}/%o}
CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(BIN) $(NAME)

submodules:
	@if git submodule status | egrep -q '^[-+]' ; then \
		echo "INFO: Need to reinitialize git submodules"; \
			git submodule update --init; \
	fi

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

${BIN}/%o: src/%c
	${CC} -c $< ${CFLAGS} ${IFLAGS} -o $@

${BIN}: | submodules
	@mkdir -p ${BIN}

$(NAME): $(OBJS) | libmlx libft
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
	$(CC) ${OBJS} $(CCFLAGS) $(INCLUDES) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✔️"

libft:
	@make -C $(LIBFT) --no-print-directory

clean:
	@${RM} ${BIN}
	@echo "$(RED) OBJS $(BLUE)successfully deleted"

fclean: clean
	make fclean -C $(LIBFT)
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) $(BLUE)successfully deleted"

re: fclean all

.PHONY: all clean fclean re submodules
