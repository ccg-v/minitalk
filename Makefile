# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 20:00:04 by ccarrace          #+#    #+#              #
#    Updated: 2023/02/20 22:33:42 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# .................................. Constants .................................

CC 				= 	gcc

CFLAGS 			= 	-MD -Wall -Wextra -Werror

# .............................. Macros/variables ..............................

HEADER 			= 	minitalk.h

NAME_SERVER		=	server
SRCS_SERVER		= 	server.c
OBJS_SERVER 	= 	$(SRCS_SERVER:.c=.o)
DEPS_SERVER		= 	$(OBJS_SERVER:.o=.d)

NAME_CLIENT		= 	client
SRCS_CLIENT		=	client.c
OBJS_CLIENT 	= 	$(SRC_CLIENT:.c=.o)
DEPS_CLIENT		= 	$(DEPS_SERVER:.o=.d)

# ................................... Rules ...................................

all:	$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER):	$(OBJS_SERVER)
					$(CC) $(FLAGS) $(SRCS_SERVER) -o server

$(NAME_CLIENT):	$(OBJS_CLIENT)
					$(CC) $(FLAGS) $(SRCS_CLIENT) -o client


# ................................. Cleaning ..................................

clean:
					rm -f $(SERVER_OBJS) $(CLIENT_OBJS)

fclean:	clean

re:		fclean all

.PHONY:	all clean fclean re
