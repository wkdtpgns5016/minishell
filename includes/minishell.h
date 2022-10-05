/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:45:00 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/28 08:48:21 by sunwchoi         ###   ########.fr       */
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
# include <term.h>
# include <sys/ioctl.h>
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

# define HERE_DOC_PATH "../here_doc"

/*
** struct define
*/
typedef struct s_cmds
{
	char			**cmd;
	int				fd[2];
	pid_t			pid;
	struct s_cmds	*next;
	struct s_cmds	*pred;
	char			*heredoc_filepath;
	int				heredoc_flag;
}	t_cmds;

typedef struct s_info
{
	t_cmds	*cmds;
	t_ev	ev;
	int		backup[2];
	int		*recent_exit_code;
	char	**envp;
	char	*history_cmd;
}	t_info;

typedef struct s_cursor
{
	int	col;
	int	row;
}	t_cursor;

typedef struct s_builtin_info
{
	int		flag;
	int		backup[2];
}	t_builtin_info;

/*
** ft_free.c
*/
void	ft_free(void **ptr);
void	free_cmds(t_cmds **cmds);
void	ft_free_arr(char ***arr);

t_cmds	*make_cmd(char *content, t_info *info);
void	add_cmd_back(t_cmds **cmds, t_cmds *node);
t_cmds	*make_cmds(char *new, t_info *info);

void	set_info(t_info *info, char *line);
t_cmds	*set_cmds(t_info *info, char *line);

char	*make_cmd_redir(char *content);
char	*make_cmd_pipe(char *content);
char	*make_cmd_pipe_amd_redir(char *line);
int		check_last_pipe(char *line);
char	*add_last_cmd(char *str, t_info *info);

void	del_heredoc_file(t_cmds *cmds);
char	**remove_redir(char **cmd, int start, int end);
int		is_redir(char *c);
void	process_redir(char **cmd, int flag, int index, int heredoc_flag, t_info *info);
void	out_redir(int src, char *outfile, int flag);
int		write_heredoc_file(int fd, char **buffer, char *limiter, t_info *info);
char	*get_heredoc(char *limiter, t_info *info);

void	in_redir(int dst, char *infile, int heredoc_flag);
int		is_num_str(char *str);
void	redirection(t_cmds *cmds, t_info *info);
char	*make_temp_file(void);

int		*make_exit_code(int	**arr, int size);
int		quit_exit_cmd(t_info *info, int signal_flag);

int		exec_builtin(t_cmds *cmds, t_info *info, int backup[2], int size);
void	exec_another(t_cmds *cmds, char **envp, t_info *info);
void	exec_cmd(t_info *info);
void	execute_cmd(char **cmd, char **envp);
void	set_info_backup_fd(t_info *info);
int		check_builtin(char **cmd);

void	wait_child(t_cmds *cmds, int **exit_code, int status2);

int		get_exit_status(int status);
int		is_exit_by_signal(int status);
int		get_exit_signal_number(int status);

void	error_excute(char *cmd, char *token, char *msg, int exit_code);
void	print_error_message(char *cmd, char *msg);
int		print_error_message_syntax(char *token);
void	print_error_message_with_token(char *cmd, char *token, char *msg);

int		is_include_str(char *big, char *little, int len);
int		check_str_before_and_after(char **token_arr, int index);
int		check_pipe(char **token_arr, int i);
int		check_redir(char **token, int i);
int		check_readline(char *line);
void	change_cmd(char **cmd, t_info	*info);
char	**make_heredoc(char *content, t_cmds *cmds, t_info *info);

void	get_cursor_position(int *col, int *rows);
void	move_cursor(int col, int row);
int		setting(t_info *info, char **envp);

char	*we_meet_char(char *cmd, t_list **cmd_char_list);
char	*we_meet_dollar(char *cmd, t_info *info, t_list **cmd_char_list);
char	*we_meet_quotes(char *cmd, t_info *info, t_list **cmd_char_list);
void	change_first_node(t_list **first_node);
void	change_node(t_list **first_node, t_info *info);
char	*list2dollar(t_list **first_node);
char	*list2char(t_list **first_node);
t_list	*char2list(char *cmd, t_info *info);
void	change_line(char **line, t_info *info);

#endif
