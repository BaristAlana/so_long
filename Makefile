# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 10:55:12 by aherbin           #+#    #+#              #
#    Updated: 2024/10/15 16:59:41 by aherbin          ###   ########.fr        #
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

EMCC := emcc -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=1 -s NO_EXIT_RUNTIME=1 -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -s ALLOW_MEMORY_GROWTH -D_WEB_ASM_=1
NAME_JS := so_long.js
SRC_WEB := src_web/so_long.c src_web/utils.c src_web/map_tools.c src_web/flood_fill.c src_web/window.c src_web/movement.c src_web/score.c src_web/win_utils.c
BIN_WEB := bin_web
OBJS_WEB = ${SRC_WEB:src_web/%c=${BIN_WEB}/%o}


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

submodules:
	@if git submodule status | egrep -q '^[-+]' ; then \
		echo "INFO: Need to reinitialize git submodules"; \
			git submodule update --init; \
	fi

web: $(BIN_WEB) $(NAME_JS)

$(NAME_JS): $(LIBMLXAR) $(LIBFTAR) $(OBJS_WEB)
	$(EMCC) ${OBJS_WEB} $(INCLUDES) $(LIBS) -o $(NAME_JS)

${BIN_WEB}/%o: src_web/%c
	$(EMCC) -c $< ${CFLAGS} ${IFLAGS} -o $@

${BIN_WEB}:
	@make submodules
	@mkdir -p ${BIN_WEB}

${BIN}/%o: src/%c
	@${CC} -c $< ${CFLAGS} ${IFLAGS} -o $@
	@echo "$(BLUE)Compiling $(GREEN)$@ $(BLUE)..."

${BIN}:
	@make submodules
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
	@$(RM) ${BIN_WEB}
	@echo "$(CYAN)$(NAME) $(RED)OBJS $(BLUE)successfully deleted\n"

fclean: clean
	@make fclean -C $(LIBFT) --no-print-directory
	@echo ""
	@$(RM) $(NAME)
	@$(RM) $(NAME_JS)
	@$(RM) $(LIBMLXAR)
	@echo "$(CYAN)$(NAME) $(BLUE)successfully deleted"

re: fclean all

.PHONY: all clean fclean re submodules web
