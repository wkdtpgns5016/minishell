# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 15:20:00 by sehjang           #+#    #+#              #
#    Updated: 2022/07/20 15:26:19 by sunwchoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = minishell

SRCS = 

SRCS_MANDATORY = srcs/setting.c \
				 srcs/main.c \
				 srcs/parsing.c \
				 srcs/ft_free.c \
				 srcs/exec_builtin.c \
				 srcs/exec_cmd.c \
				 srcs/builtin_cmd.c \
				 srcs/builtin_cmd2.c \
				 srcs/builtin_utils.c \
				 srcs/builtin_utils2.c
SRCS_BONUS = 

#COMFILE_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
#OBJ_FLAGS = -I${HOME}/.brew/opt/readline/include
COMFILE_FLAGS= -lreadline -L/usr/local/opt/readline/lib
OBJ_FLAGS=-I/usr/local/opt/readline/include
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
	$(CC) $(CFLAGS) $(OBJ_FLAGS) -c -I $(HEAD) $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C ./libft bonus
	$(CC) $(CFLAGS) $(COMFILE_FLAGS) $(OBJS) -Llibft -lft -o $(NAME)

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
