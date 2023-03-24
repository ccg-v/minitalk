# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 20:00:04 by ccarra:ce          #+#    #+#             #
#    Updated: 2023/03/24 21:29:39 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# |------------------------|        Constants        |-----------------------| #

YELLOW 			= 	\033[0;93m
BOLD_YELLOW		=	\033[1;33m
DEF_COLOR		=	\033[0m

CC				= 	gcc
CFLAGS 			= 	-MD -Wall -Wextra -Werror
HEADER 			= 	minitalk.h

LIBFT_NAME		=	libft.a
LIBFT_DIR		=	libft/
LIBFT_SRCS		=	$(LIBFT_DIR)$(LIBFT_NAME)

# Mandatory

SERVER_NAME		=	server
SERVER_SRCS		= 	server.c

CLIENT_NAME		= 	client
CLIENT_SRCS		=	client.c

# Bonus

B_SERVER_NAME	= 	server_bonus
B_SERVER_SRCS	=	server_bonus.c

B_CLIENT_NAME	=	client_bonus
B_CLIENT_SRCS	=	client_bonus.c

# |-----------------------|     Macros/variables     |-----------------------| #

# Mandatory

SERVER_OBJS		=	$(SERVER_SRCS:.c=.o)
SERVER_DEPS		=	$(SERVER_OBJS:.o=.d)

CLIENT_OBJS		=	$(CLIENT_SRCS:.c=.o)
CLIENT_DEPS		=	$(CLIENT_OBJS:.o=.d)
 
# Bonus

B_SERVER_OBJS	=	$(B_SERVER_SRCS:.c=.o)
B_SERVER_DEPS	=	$(B_SERVER_OBJS:.o=.d)

B_CLIENT_OBJS	=	$(B_CLIENT_SRCS:.c=.o)
B_CLIENT_DEPS	=	$(B_CLIENT_OBJS:.o=.d)

# Common

OBJS_DEPS_LST	=	$(shell find . -maxdepth 2 -name '*.o' -o -name '*.d')
EXECUTS_LST		=	$(shell find . -maxdepth 2 -name $(SERVER_NAME) \
					-o -name $(CLIENT_NAME) -o -name $(B_SERVER_NAME) \
					-o -name $(B_CLIENT_NAME) -o -name $(LIBFT_NAME))

# |-----------------------|    Compilation rules     |-----------------------| #

# Mandatory

all:			
				@$(MAKE) -s -C $(LIBFT_DIR)
				@$(MAKE) -s $(SERVER_NAME) 
				@$(MAKE) -s $(CLIENT_NAME)

$(SERVER_NAME):	$(HEADER) $(SERVER_OBJS) 
				$(CC) $(CFLAGS) $(SERVER_SRCS) -L$(LIBFT_DIR) -lft -o $(SERVER_NAME)
				$(MSG_OK_SERVER)

$(CLIENT_NAME):	$(HEADER) $(CLIENT_OBJS)
				$(CC) $(CFLAGS) $(CLIENT_SRCS) -L$(LIBFT_DIR) -lft -o $(CLIENT_NAME)
				$(MSG_OK_CLIENT)

# Bonus

bonus:			
					@$(MAKE) -s -C $(LIBFT_DIR)
					@$(MAKE) -s $(B_SERVER_NAME) 
					@$(MAKE) -s $(B_CLIENT_NAME)

$(B_SERVER_NAME):	$(HEADER) $(B_SERVER_OBJS)
					$(CC) $(CFLAGS) $(B_SERVER_SRCS)  -L$(LIBFT_DIR) -lft -o $(B_SERVER_NAME)
					$(MSG_OK_B_SERVER)

$(B_CLIENT_NAME):	$(HEADER) $(B_CLIENT_OBJS)
					$(CC) $(CFLAGS) $(B_CLIENT_SRCS)  -L$(LIBFT_DIR) -lft -o $(B_CLIENT_NAME)
					$(MSG_OK_B_CLIENT)

# Common

#%.o: %.c
#	${CC} ${CFLAGS} -c $< -o $@

# |-----------------------|         Messages         |-----------------------| #

MSG_OK_SERVER	=	echo "$(BOLD_YELLOW)Server executable compiled$(DEF_COLOR)"
MSG_OK_CLIENT	=	echo "$(BOLD_YELLOW)Client executable compiled$(DEF_COLOR)"
MSG_OK_B_SERVER	=	echo "$(BOLD_YELLOW)Server bonus executable compiled$(DEF_COLOR)"
MSG_OK_B_CLIENT	=	echo "$(BOLD_YELLOW)Client bonus executable compiled$(DEF_COLOR)"
MSG_CLEAN		=	echo "$(BOLD_YELLOW)Removing object and dependency files...$(DEF_COLOR)"
MSG_FCLEAN		=	echo "$(BOLD_YELLOW)Removing executable files...$(DEF_COLOR)"

# |-----------------------|      Cleaning rules      |-----------------------| #

clean:
		@rm -f $(SERVER_DEPS) $(SERVER_OBJS) $(CLIENT_DEPS) $(CLIENT_OBJS)
		@rm -f $(B_SERVER_DEPS) $(B_SERVER_OBJS) $(B_CLIENT_DEPS) $(B_CLIENT_OBJS)
		@$(MAKE) clean -C $(LIBFT_DIR)
		@$(MSG_CLEAN)

ifeq ($(strip $(OBJS_DEPS_LST)),)
	@echo "No object or dependency files found to remove"
else
	@echo "$(YELLOW)$(OBJS_DEPS_LST)$(DEF_COLOR) deleted"
endif

fclean:	clean
		@rm -f $(SERVER_NAME) $(CLIENT_NAME) 
		@rm -f $(B_SERVER_NAME) $(B_CLIENT_NAME)
		@$(MAKE) fclean -C $(LIBFT_DIR)
		@$(MSG_FCLEAN)

ifeq ($(strip $(EXECUTS_LST)),)
	@echo "No executable files found to remove"
else
	@echo "$(YELLOW)$(EXECUTS_LST)$(DEF_COLOR) deleted"
endif
		
re:			fclean all

rebonus:	fclean bonus

.PHONY:	all clean fclean re rebonus

#-include $(SERVER_DEPS) $(CLIENT_DEPS) $(B_SERVER_DEPS) $(B_CLIENT_DEPS) *.d
