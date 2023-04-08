# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 19:55:46 by ccarrace          #+#    #+#              #
#    Updated: 2023/04/03 19:48:09 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -MMD -Wall -Wextra -Werror

HEADER = libft.h

SRC_FILES = ft_isalpha.c \
	  		ft_isdigit.c \
	  		ft_isalnum.c \
	  		ft_isascii.c \
	  		ft_isprint.c \
	  		ft_strlen.c \
	  		ft_memset.c \
	  		ft_bzero.c \
	  		ft_memcpy.c \
	  		ft_memmove.c \
	  		ft_strlcpy.c \
	  		ft_strlcat.c \
	  		ft_toupper.c \
	  		ft_tolower.c \
	  		ft_strchr.c \
	  		ft_strrchr.c \
	  		ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
	  		ft_strnstr.c \
	  		ft_atoi.c \
	  		ft_calloc.c \
	  		ft_strdup.c \
	  		ft_substr.c \
	  		ft_strjoin.c \
	  		ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
	  		ft_putchar_fd.c \
	  		ft_putstr_fd.c \
	  		ft_putendl_fd.c \
	  		ft_putnbr_fd.c 

BONUS_FILES = ft_lstnew_bonus.c \
			  ft_lstadd_front_bonus.c \
			  ft_lstsize_bonus.c \
			  ft_lstlast_bonus.c \
			  ft_lstadd_back_bonus.c \
			  ft_lstdelone_bonus.c \
			  ft_lstclear_bonus.c \
			  ft_lstiter_bonus.c \
			  ft_lstmap_bonus.c \
			  $(SRC_FILES)

DEPS = $(SRC_FILES:.c=.d)
DEPS += $(BONUS_FILES:.c=.d)
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_BONUS_FILES = $(BONUS_FILES:.c=.o)

$(NAME): $(HEADER) $(OBJ_FILES) 
	ar -rcs $(NAME) $(OBJ_FILES)
	@echo "Library libft compiled"

all: $(NAME)

bonus: $(HEADER) $(OBJ_BONUS_FILES)
	ar -rcs $(NAME) $(OBJ_BONUS_FILES)
	touch bonus

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ_FILES) $(OBJ_BONUS_FILES) $(DEPS)

fclean: 
	@rm -f $(OBJ_FILES) $(OBJ_BONUS_FILES) $(DEPS)
	rm -f $(NAME)
	rm -f bonus
	
re: fclean all

.PHONY: all, bonus, clean, fclean, re

-include $(DEPS)	
