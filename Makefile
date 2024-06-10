# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 10:55:12 by aherbin           #+#    #+#              #
#    Updated: 2024/06/10 11:19:26 by aherbin          ###   ########.fr        #
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
MLX42AR := $(LIBMLX)/build/libmlx42.a
LIBFTAR := $(LIBFT)/libft.a

CYAN := \033[1;36m
GREEN := \033[1;32m
RED := \033[1;31m
BLUE := \033[0;34m

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

${BIN}:
	@mkdir -p ${BIN}

$(MLX42AR): libmlx

$(LIBFTAR): libft

$(NAME): submodules $(OBJS) | $(LIBFTAR) $(MLX42AR)
	$(CC) ${OBJS} $(CCFLAGS) $(INCLUDES) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$@ $(BLUE)successfully compiled"

libft:
	@make -C $(LIBFT) --no-print-directory

clean:
	@${RM} ${BIN} ${DEBUGBIN}
	@echo "$(RED) OBJS $(BLUE)successfully deleted"

fclean: clean
	make fclean -C $(LIBFT)
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) $(BLUE)successfully deleted"

re: fclean all

.PHONY: all clean fclean re ${libmlx} ${LIBFT} submodules
