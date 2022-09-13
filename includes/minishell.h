/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:45:00 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/14 01:53:09 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** include header file
*/
# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <termios.h>
# include "./setting.h"
# include "./builtin_cmd.h"
# include "./signal.h"

/*
** flag number
*/
# define INPUT_REDIR 1
# define HERE_DOC_REDIR 2
# define OUTPUT_TRUNC_REDIR 3
# define OUTPUT_APPAND_REDIR 4
# define PIPE_LINE 5

typedef struct s_cmds
{
	char			**cmd;
	int				fd[2];
	struct s_cmds	*next;
	struct s_cmds	*pred;
}	t_cmds;

typedef struct s_info
{
	t_cmds	*cmds;
	t_ev	ev;
	int		backup[2];
	int		recent_exit_code;
	char	**envp;
}	t_info;

typedef struct s_builtin_info
{
	int		flag;
	int		backup[2];
}	t_builtin_info;

void	ft_free(void **ptr);
void	free_cmds(t_cmds **cmds);
void	ft_free_arr(char ***arr);

//t_info	set_info(t_info info, char **line);

void	set_info(t_info *info, char *line);
t_cmds	*set_cmds(t_info *info, char *line);

char	*make_cmd_redir(char *content);
char	*make_cmd_pipe(char *content);
char	*make_cmd_pipe_amd_redir(char *line);
int		check_last_pipe(char *line);

char	**remove_redir(char **cmd, int start, int end);
int		is_redir(char *c);
void	process_redir(char **cmd, int flag, int index, int backup[2]);
void	process_redir_with_num(char **cmd, int flag, int index, int backup[2]);
void	out_redir(int src, char *outfile, int flag);
void	get_heredoc(char *limiter, int backup_in);
void	in_redir(int dst, char *infile);
int		is_num_str(char *str);
void	redirection(t_cmds *cmds, int backup[2]);

int		exec_builtin(t_cmds *cmds, t_ev *ev, int backup[2], int size);
int		exec_another(t_cmds *cmds, char **envp, int backup[2]);
void	exec_cmd(t_info *info);
void	execute_cmd(char **cmd, char **envp);
void	set_info_backup_fd(t_info *info);
int		get_exit_status(int status);
int		check_builtin(char **cmd);

void	error_excute(char *cmd, char *token, char *msg, int exit_code);
int		print_error_message_syntax(char *token);
void	print_error_message_with_token(char *cmd, char *token, char *msg);

int		is_include_str(char *big, char *little, int len);
int		check_str_before_and_after(char **token_arr, int index);
int		check_pipe(char **token_arr, int i);
int		check_redir(char **token, int i);
int		check_readline(char *line);
void	change_cmd(char **cmd, t_info	*info);

#endif
