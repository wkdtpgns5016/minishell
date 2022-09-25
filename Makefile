# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 15:20:00 by sehjang           #+#    #+#              #
#    Updated: 2022/09/25 19:58:56 by sunwchoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra 

NAME = minishell

SRCS = 

SRCS_MANDATORY = srcs/main.c \
				 srcs/parsing/parsing.c \
				 srcs/parsing/parsing_utils.c \
				 srcs/parsing/parsing_utils2.c \
				 srcs/parsing/parsing_utils3.c \
				 srcs/parsing/change_cmd_with_list.c \
				 srcs/parsing/change_cmd_with_list1.c \
				 srcs/parsing/parsing_utils5.c \
				 srcs/setting/signal.c \
				 srcs/setting/setting.c \
				 srcs/setting/cursor.c \
				 srcs/utils/ft_free.c \
				 srcs/utils/wait_status.c \
				 srcs/utils/error_handling.c \
				 srcs/execute/execute_cmd.c \
				 srcs/execute/exec_cmd.c \
				 srcs/execute/exec_cmd_utils.c \
				 srcs/execute/exec_another.c \
				 srcs/execute/exec_builtin.c \
				 srcs/execute/exec_utils.c \
				 srcs/execute/builtin/builtin_cmd.c \
				 srcs/execute/builtin/builtin_cmd2.c \
				 srcs/execute/builtin/builtin_cmd3.c \
				 srcs/execute/builtin/builtin_utils.c \
				 srcs/execute/builtin/builtin_utils2.c \
				 srcs/redirection/redirection.c \
				 srcs/redirection/redirection_utils.c \
				 srcs/redirection/redirection_utils2.c \
				 srcs/syntax/check_readline.c \
				 srcs/syntax/check_pipe.c \
				 srcs/syntax/check_redir.c
SRCS_BONUS = 

COMFILE_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
OBJ_FLAGS = -I${HOME}/.brew/opt/readline/include
#COMFILE_FLAGS= -lreadline -L/usr/local/opt/readline/lib
#OBJ_FLAGS=-I/usr/local/opt/readline/include
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
	$(CC) -g $(CFLAGS) $(OBJ_FLAGS) -c -I $(HEAD) $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C ./libft bonus
	$(CC) -g $(CFLAGS) $(COMFILE_FLAGS) $(OBJS) -Llibft -lft -o $(NAME) -lncurses

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
