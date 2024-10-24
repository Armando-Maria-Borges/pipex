# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aborges <aborges@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 08:37:26 by aborges           #+#    #+#              #
#    Updated: 2024/07/17 12:21:31 by aborges          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I include

SRC = pipex.c aux.c
OBJ = $(SRC:.c=.o)
EXEC = pipex

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)
	@clear
	@echo "\033[1;32mSeja bem-vindo! '$(EXEC)' executado com sucesso.\033[0m"

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@clear
	@echo "\033[1;33mArquivos objeto foram removidos.\033[0m"

fclean: clean
	rm -f $(EXEC)
	@echo "\033[1;32mExecutável foi removido.\033[0m"

re: fclean all

.PHONY: all clean fclean re