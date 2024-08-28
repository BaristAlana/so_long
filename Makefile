# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 10:55:12 by aherbin           #+#    #+#              #
#    Updated: 2024/08/28 16:59:00 by aherbin          ###   ########.fr        #
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

all: submodules $(BIN) $(NAME)

submodules:
	@if git submodule status | egrep -q '^[-+]' ; then \
		echo "INFO: Need to reinitialize git submodules"; \
			git submodule update --init; \
	fi

${BIN}/%o: src/%c
	@${CC} -c $< ${CFLAGS} ${IFLAGS} -o $@
	@echo "$(BLUE)Compiling $(GREEN)$@ $(BLUE)..."

${BIN}:
	@mkdir -p ${BIN}

$(NAME): $(LIBMLXAR) $(LIBFTAR) $(OBJS)
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${CYAN}$(NAME) ${CLR_RMV}..."
	@$(CC) ${OBJS} $(CCFLAGS) $(INCLUDES) $(LIBS) -o $(NAME)
	@echo "$(CYAN)$(NAME)$(BLUE) compiled $(GREEN)✔️$(CLR_RMV)"

$(LIBFTAR):
	@echo "$(YELLOW)----- Libft -----$(CLR_RMV)"
	@make -C $(LIBFT) --no-print-directory
	@echo "$(YELLOW)-----------------\n$(CLR_RMV)"

$(LIBMLXAR):
	@echo "$(YELLOW)----- MLX42 -----$(CLR_RMV)"
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 --no-print-directory
	@echo "$(YELLOW)-----------------\n$(CLR_RMV)"

clean:
	@${RM} ${BIN}
	@echo "$(CYAN)$(NAME) $(RED)OBJS $(BLUE)successfully deleted\n"

fclean: clean
	@make fclean -C $(LIBFT) --no-print-directory
	@echo ""
	@$(RM) $(NAME)
	@$(RM) $(LIBMLXAR)
	@echo "$(CYAN)$(NAME) $(BLUE)successfully deleted"

re: fclean all

.PHONY: all clean fclean re submodules
