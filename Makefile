# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 20:00:04 by ccarra:ce          #+#    #+#             #
#    Updated: 2023/03/08 23:18:25 by ccarrace         ###   ########.fr        #
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

PRINTF_NAME		= 	libftprintf.a
PRINTF_DIR		=	ft_printf/
PRINTF_SRCS		=	$(PRINTF_DIR)$(PRINTF_NAME)

# Mandatory

SERVER_NAME		=	server
SERVER_SRCS		= 	server.c

CLIENT_NAME		= 	client
CLIENT_SRCS		=	client.c

# Bonus

B_SERVER_NAME	= 	bonus_server
B_SERVER_SRCS	=	bonus_server.c

B_CLIENT_NAME	=	bonus_client
B_CLIENT_SRCS	=	bonus_client.c

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
EXECUTS_LST		=	$(shell find . -maxdepth 1 -name $(SERVER_NAME) \
					-o -name $(CLIENT_NAME) -o -name $(B_SERVER_NAME) \
					-o -name $(B_CLIENT_NAME) -o -name $(LIBFT_NAME) \
					-o -name $(PRINTF_NAME))

# |-----------------------|    Compilation rules     |-----------------------| #

# Mandatory

all:			
				@$(MAKE) -s -C $(LIBFT_DIR)
				@$(MAKE) -s -C $(PRINTF_DIR)
				@$(MAKE) -s $(SERVER_NAME) 
				@$(MAKE) -s $(CLIENT_NAME)

$(SERVER_NAME):	$(HEADER) $(SERVER_OBJS) $(LIBFT_SRCS) $(PRINTF_SRCS)
				$(CC) $(FLAGS) $(SERVER_SRCS) $(LIBFT_SRCS) $(PRINTF_SRCS) -o $(SERVER_NAME)
				$(MSG_OK_SERVER)

$(CLIENT_NAME):	$(HEADER) $(CLIENT_OBJS) $(LIBFT_SRCS) $(PRINTF_SRCS)
				$(CC) $(FLAGS) $(CLIENT_SRCS) $(LIBFT_SRCS) $(PRINTF_SRCS) -o $(CLIENT_NAME)
				$(MSG_OK_CLIENT)

# Bonus

bonus:			
				@$(MAKE) -s -C $(LIBFT_DIR)
				@$(MAKE) -s -C $(PRINTF_DIR)
				@$(MAKE) -s $(B_SERVER_NAME) 
				@$(MAKE) -s $(B_CLIENT_NAME)

$(B_SERVER_NAME):	$(HEADER) $(B_SERVER_OBJS) $(LIBFT_SRCS) $(PRINTF_SRCS)
				$(CC) $(FLAGS) $(B_SERVER_SRCS) $(LIBFT_SRCS) $(PRINTF_SRCS) -o $(B_SERVER_NAME)
				$(MSG_OK_B_SERVER)

$(B_CLIENT_NAME):	$(HEADER) $(B_CLIENT_OBJS) $(LIBFT_SRCS) $(PRINTF_SRCS)
				$(CC) $(FLAGS) $(B_CLIENT_SRCS) $(LIBFT_SRCS) $(PRINTF_SRCS) -o $(B_CLIENT_NAME)
				$(MSG_OK_B_CLIENT)

# |-----------------------|         Messages         |-----------------------| #

MSG_OK_SERVER	=	echo "$(BOLD_YELLOW)Server executable compiled$(DEF_COLOR)"
MSG_OK_CLIENT	=	echo "$(BOLD_YELLOW)Client executable compiled$(DEF_COLOR)"
MSG_OK_B_SERVER	=	echo "$(BOLD_YELLOW)Bonus server executable compiled$(DEF_COLOR)"
MSG_OK_B_CLIENT	=	echo "$(BOLD_YELLOW)Bonus client executable compiled$(DEF_COLOR)"
MSG_CLEAN		=	echo "$(BOLD_YELLOW)Removing object and dependency files...$(DEF_COLOR)"
MSG_FCLEAN		=	echo "$(BOLD_YELLOW)Removing executable files...$(DEF_COLOR)"

# |-----------------------|      Cleaning rules      |-----------------------| #

clean:
		@rm -f $(SERVER_DEPS) $(SERVER_OBJS) $(CLIENT_DEPS) $(CLIENT_OBJS)
		@rm -f $(B_SERVER_DEPS) $(B_SERVER_OBJS) $(B_CLIENT_DEPS) $(B_CLIENT_OBJS)
		@$(MAKE) clean -C $(LIBFT_DIR)
		@$(MAKE) clean -C $(PRINTF_DIR)
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
		@$(MAKE) fclean -C $(PRINTF_DIR)
		@$(MSG_FCLEAN)

ifeq ($(strip $(EXECUTS_LST)),)
	@echo "No executable files found to remove"
else
	@echo "$(YELLOW)$(EXECUTS_LST)$(DEF_COLOR) deleted"
endif
		
re:		fclean all

.PHONY:	all clean fclean re bonus
