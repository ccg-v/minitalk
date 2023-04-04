# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 20:00:04 by ccarra:ce          #+#    #+#             #
#    Updated: 2023/04/03 19:50:53 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Constants -------------------------------------------------------------- #

CC				= 	gcc
CFLAGS 			= 	-MMD -Wall -Wextra -Werror
HEADER_NAME		= 	minitalk.h

LIB_NAME		=	libft.a

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

# --- Paths ------------------------------------------------------------------ #

LIB_DIR       	=   libft/
HEADERS_DIR		= 	libft/
INCLUDE_LIB		=	-L $(LIB_DIR) -lft
INCLUDE_HEADER	=	-I $(HEADERS_DIR)

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
					-o -name $(B_CLIENT_NAME) -o -name $(LIB_NAME))

# |-----------------------|    Compilation rules     |-----------------------| #

# Mandatory

all:			
				$(MAKE) -C $(LIB_DIR)
				$(MAKE) $(SERVER_NAME)
				$(MAKE) $(CLIENT_NAME)	

$(SERVER_NAME):	$(SERVER_OBJS) $(LIB_DIR)$(LIB_NAME)
				$(CC) $(CFLAGS) $(SERVER_OBJS) $(INCLUDE_LIB) -o $@
				@$(MSG_OK_SERVER)

$(CLIENT_NAME):	$(CLIENT_OBJS) $(LIB_DIR)$(LIB_NAME)
				$(CC) $(CFLAGS) $(CLIENT_OBJS) $(INCLUDE_LIB) -o $@
				@$(MSG_OK_CLIENT)

# Bonus

bonus:			
					$(MAKE) -C $(LIB_DIR)
					$(MAKE) $(B_SERVER_NAME) 
					$(MAKE) $(B_CLIENT_NAME)

$(B_SERVER_NAME):	$(B_SERVER_OBJS) $(LIB_DIR)$(LIB_NAME)
					$(CC) $(CFLAGS) $(B_SERVER_OBJS) $(INCLUDE_LIB) -o $@
					@$(MSG_OK_B_SERVER)

$(B_CLIENT_NAME):	$(B_CLIENT_OBJS) $(LIB_DIR)$(LIB_NAME)
					$(CC) $(CFLAGS) $(B_CLIENT_OBJS) $(INCLUDE_LIB) -o $@
					@$(MSG_OK_B_CLIENT)

# Common

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIB_DIR) -c $< -o $@

-include $(SERVER_DEPS) $(CLIENT_DEPS) $(B_SERVER_DEPS) $(B_CLIENT_DEPS)

# |-----------------------|      Cleaning rules      |-----------------------| #

clean:

ifeq ($(strip $(OBJS_DEPS_LST)),)
	@$(MSG_NO_CLEAN)
else
	rm -f $(SERVER_OBJS) $(SERVER_DEPS) $(CLIENT_OBJS) $(CLIENT_DEPS)
	rm -f $(B_SERVER_OBJS) $(B_SERVER_DEPS) $(B_CLIENT_OBJS) $(B_CLIENT_DEPS)
	@$(MAKE) clean -C $(LIB_DIR)
	@$(MSG_OK_CLEAN)
endif

fclean:	clean

ifeq ($(strip $(EXECUTS_LST)),)
	@$(MSG_NO_FCLEAN)
else
	rm -f $(SERVER_NAME) $(CLIENT_NAME) 
	rm -f $(B_SERVER_NAME) $(B_CLIENT_NAME)
	@$(MAKE) fclean -C $(LIB_DIR)
	@$(MSG_OK_FCLEAN)
endif
		
re:			fclean all

rebonus:	fclean bonus

# --- Colors ----------------------------------------------------------------- #

YELLOW 			= 	\033[0;93m
BOLD_YELLOW		=	\033[1;33m
DEF_COLOR		=	\033[0m

# |-----------------------|         Messages         |-----------------------| #

MSG_OK_SERVER	=	echo "$(BOLD_YELLOW)Server executable compiled$(DEF_COLOR)"
MSG_OK_CLIENT	=	echo "$(BOLD_YELLOW)Client executable compiled$(DEF_COLOR)"
MSG_OK_B_SERVER	=	echo "$(BOLD_YELLOW)Server bonus executable compiled$(DEF_COLOR)"
MSG_OK_B_CLIENT	=	echo "$(BOLD_YELLOW)Client bonus executable compiled$(DEF_COLOR)"
MSG_OK_CLEAN	=	echo "$(BOLD_YELLOW)Object and dependency files removed$(DEF_COLOR)"
MSG_NO_CLEAN	=	echo "$(BOLD_YELLOW)No object or dependency files to remove$(DEF_COLOR)"
MSG_OK_FCLEAN	=	echo "$(BOLD_YELLOW)Executable files removed$(DEF_COLOR)"
MSG_NO_FCLEAN	=	echo "$(BOLD_YELLOW)No executable files found to remove$(DEF_COLOR)"

.PHONY:	all clean fclean re rebonus

