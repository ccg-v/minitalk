# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 20:00:04 by ccarra:ce          #+#    #+#             #
#    Updated: 2023/02/23 23:29:50 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# |------------------------|        Constants        |-----------------------| #

YELLOW 			= 	\033[0;93m
DEFAULT_COLOR	=	\033[0m

CC 				= 	gcc
CFLAGS 			= 	-MD -Wall -Wextra -Werror

SERVER_NAME		=	server
SERVER_SRCS		= 	server.c

CLIENT_NAME		= 	client
CLIENT_SRCS		=	client.c

HEADER 			= 	minitalk.h

LIBFT_NAME		=	libft
LIBFT_SRCS		=	libft/libft.a
LIBFT_DIR		=	libft/

# |-----------------------|     Macros/variables     |-----------------------| #

SERVER_OBJS 	= 	$(SERVER_SRCS:.c=.o)
SERVER_DEPS		= 	$(SERVER_OBJS:.o=.d)

CLIENT_OBJS 	= 	$(CLIENT_SRCS:.c=.o)
CLIENT_DEPS		= 	$(CLIENT_OBJS:.o=.d)

#OBJS_COUNT		=	$(shell ls *.o *.d | wc -l | sed 's/ //g') 
OBJS_DEPS_LIST	=	$(shell find . -maxdepth 1 -name '*.o' -o -name '*.d')
EXEC_LIST		=	$(shell find . -maxdepth 1 -name $(SERVER_NAME) -o -name $(CLIENT_NAME))

# |-----------------------|    Compilation rules     |-----------------------| #

all:			$(SERVER_NAME) $(CLIENT_NAME)
				$(MAKE) -C $(LIBFT_DIR)

$(SERVER_NAME):	$(SERVER_OBJS) $(HEADER) 
				$(CC) $(FLAGS) $(SERVER_SRCS) -o $(SERVER_NAME)

$(CLIENT_NAME):	$(CLIENT_OBJS) $(HEADER) 
				$(CC) $(FLAGS) $(CLIENT_SRCS) -o $(CLIENT_NAME)

# |-----------------------|      Cleaning rules      |-----------------------| #

clean:
		@rm -f $(SERVER_DEPS) $(SERVER_OBJS) $(CLIENT_DEPS) $(CLIENT_OBJS)
		$(MAKE) clean -C $(LIBFT_DIR)

ifeq ($(strip $(OBJS_DEPS_LIST)),)
	@echo "No object or dependency files found. Nothing deleted"
else
	@echo "$(YELLOW)$(OBJS_DEPS_LIST)$(DEFAULT_COLOR) removed"
endif

fclean:	clean
		@rm -f $(SERVER_NAME) $(CLIENT_NAME)
		$(MAKE) fclean -C $(LIBFT_DIR)

ifeq ($(strip $(EXEC_LIST)),)
	@echo "No executables found. Nothing deleted"
else
	@echo "$(YELLOW)$(EXEC_LIST)$(DEFAULT_COLOR) removed"
endif
		
re:		fclean all

.PHONY:	all clean fclean re
