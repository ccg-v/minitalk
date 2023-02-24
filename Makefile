# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 20:00:04 by ccarra:ce          #+#    #+#             #
#    Updated: 2023/02/25 00:14:04 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# |------------------------|        Constants        |-----------------------| #

YELLOW 			= 	\033[0;93m
BOLD_YELLOW		=	\033[1;33m
DEF_COLOR		=	\033[0m

CC				= 	gcc
CFLAGS 			= 	-MD -Wall -Wextra -Werror

SERVER_NAME		=	server
SERVER_SRCS		= 	server.c

CLIENT_NAME		= 	client
CLIENT_SRCS		=	client.c

HEADER 			= 	minitalk.h

LIBFT_NAME		=	libft.a
LIBFT_DIR		=	libft/
LIBFT_SRCS		=	$(LIBFT_DIR)$(LIBFT_NAME)

# |-----------------------|     Macros/variables     |-----------------------| #

SERVER_OBJS		=	$(SERVER_SRCS:.c=.o)
SERVER_DEPS		=	$(SERVER_OBJS:.o=.d)

CLIENT_OBJS		=	$(CLIENT_SRCS:.c=.o)
CLIENT_DEPS		=	$(CLIENT_OBJS:.o=.d)
 
OBJS_DEPS_LST	=	$(shell find . -maxdepth 2 -name '*.o' -o -name '*.d')
EXECUT_LST		=	$(shell find . -maxdepth 2 -name $(SERVER_NAME) -o -name \
					$(CLIENT_NAME) -o -name $(LIBFT_NAME))

# |-----------------------|    Compilation rules     |-----------------------| #

all:			
				@$(MAKE) -s -C $(LIBFT_DIR)
				@$(MAKE) -s $(SERVER_NAME) 
				@$(MAKE) -s $(CLIENT_NAME)

$(SERVER_NAME):	$(HEADER) $(SERVER_OBJS) $(LIBFT_SRCS)
				$(CC) $(FLAGS) $(SERVER_SRCS) $(LIBFT_SRCS) -o $(SERVER_NAME)
				$(MSG_OK_SERVER)

$(CLIENT_NAME):	$(HEADER) $(CLIENT_OBJS) $(LIBFT_SRCS)
				$(CC) $(FLAGS) $(CLIENT_SRCS) $(LIBFT_SRCS) -o $(CLIENT_NAME)
				$(MSG_OK_CLIENT)

# |-----------------------|         Messages         |-----------------------| #

MSG_OK_SERVER	=	echo "$(BOLD_YELLOW)Server executable compiled$(DEF_COLOR)"
MSG_OK_CLIENT	=	echo "$(BOLD_YELLOW)Client executable compiled$(DEF_COLOR)"
MSG_CLEAN		=	echo "$(BOLD_YELLOW)Removing object and dependency files...$(DEF_COLOR)"
MSG_FCLEAN		=	echo "$(BOLD_YELLOW)Removing executable files...$(DEF_COLOR)"

# |-----------------------|      Cleaning rules      |-----------------------| #

clean:
		@rm -f $(SERVER_DEPS) $(SERVER_OBJS) $(CLIENT_DEPS) $(CLIENT_OBJS)
		@$(MAKE) clean -C $(LIBFT_DIR)
		@$(MSG_CLEAN)

ifeq ($(strip $(OBJS_DEPS_LST)),)
	@echo "No object or dependency files found to remove"
else
	@echo "$(YELLOW)$(OBJS_DEPS_LST)$(DEF_COLOR) deleted"
endif

fclean:	clean
		@rm -f $(SERVER_NAME) $(CLIENT_NAME)
		@$(MAKE) fclean -C $(LIBFT_DIR)
		@$(MSG_FCLEAN)

ifeq ($(strip $(EXECUT_LST)),)
	@echo "No object or dependency files found to remove"
else
	@echo "$(YELLOW)$(EXECUT_LST)$(DEF_COLOR) deleted"
endif
		
re:		fclean all

.PHONY:	all clean fclean re
