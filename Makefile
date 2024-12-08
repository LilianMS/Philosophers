# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/01 20:52:42 by lilmende          #+#    #+#              #
#    Updated: 2024/12/05 23:58:55 by lilmende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Wextra -Wall -Werror -g -pthread
LIBFT = ./libs/libft
HEADERS = ./include
BIN = ./bin

CC = cc

SRC = src/main.c \
	src/init_data.c \
	src/init.c \
	src/monitor.c \
	src/routine.c \
	src/tools.c \
	src/utils.c \
	src/clean.c

INCLUDE = -I$(HEADERS)

OBJS = $(patsubst src/%.c, $(BIN)/%.o, $(SRC))

# Cores para saída
RED     = \033[2;31m
GREEN   = \033[0;32m
BGREEN  = \033[0;41m
YELLOW  = \033[2;33m
BLUE    = \033[2;34m
MAGEN   = \033[0;35m
CYAN    = \033[1;36m
RESET   = \033[0m

# Regra principal
all: $(NAME)
	@echo "${YELLOW}    --    Compiled Program >>> ${GREEN}./$(NAME)${YELLOW}    --${RESET}"

# Regra para gerar arquivos objeto
$(BIN)/%.o: src/%.c
	@mkdir -p $(BIN)
	@$(CC) $(FLAGS) $(INCLUDE) -o $@ -c $< && echo "${YELLOW}Compiling:${RESET} $(notdir $<)"

# Regra para gerar o executável
$(NAME): $(OBJS)
	@echo " "
	@echo "Creating file $(NAME) ..."
	@echo " "
	@$(CC) $(OBJS) $(INCLUDE) -o $(NAME)
	@echo "${GREEN}Compilation successful!${RESET}"

# Limpar objetos
clean:
	@if ls $(BIN) 1> /dev/null 2>&1; then \
		echo "${RED}Deleting objects...${RESET}"; \
		rm -rf $(BIN); \
		echo "${YELLOW}Done.${RESET}"; \
	else \
		echo "${YELLOW}No objects to delete.${RESET}"; \
	fi

# Limpar tudo, incluindo o binário
fclean: clean
	@echo "${RED}Removing executable...${RESET}"
	@rm -rf $(NAME)
	@echo " "
	@echo " ${RED}    --    Program Removed ✔️    --${RESET}"
	@echo " "

# Reconstruir o projeto
re: fclean all

# Definir como comandos que não criam arquivos
.PHONY: all clean fclean re
