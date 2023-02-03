# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 20:00:04 by ccarrace          #+#    #+#              #
#    Updated: 2023/01/24 23:29:44 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -MD -Wall -Wextra -Werror

HEADER = minitalk.h

SRC_FILES = client.c
			server.c

OBJ_FILES = $(SRC_FILES:.c=.o)

DEP_FILES = $(OBJ_FILES:.o=.d)

all: $(NAME)

$(NAME) : $(OBJ_FILES)
	ar -rcs $(NAME) $(OBJ_FILES)


