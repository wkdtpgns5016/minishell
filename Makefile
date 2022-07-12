# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 20:03:03 by sehjang           #+#    #+#              #
#    Updated: 2022/07/12 20:03:04 by sehjang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = minishell

SRCS = 

SRCS_MANDATORY = srcs/main.c
SRCS_BONUS = 

OBJS = $(SRCS:.c=.o)
OBJS_MANDATORY = $(SRCS_MANDATORY:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJS += $(OBJS_BONUS)
else
	OBJS += $(OBJS_MANDATORY)
endif

HEAD = ./include

all: $(NAME)

%.o: %.c
	$(CC) -g $(CFLAGS) -c -I $(HEAD) $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C ./libft bonus
	$(CC) -g -o $(NAME) $(OBJS) -Llibft -lft

clean:
	$(MAKE) -C ./libft clean
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(MAKE) -C ./libft fclean
	rm -f $(NAME)

re: 
	$(MAKE) fclean 
	$(MAKE) all

bonus:
	$(MAKE) WITH_BONUS=1 all

.PHONY = all clean fclean re bonus
