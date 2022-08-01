/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:45:00 by sehjang           #+#    #+#             */
/*   Updated: 2022/07/20 14:45:01 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "./signal.h"

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
	char	**envp;
}	t_info;

void	execute_cmd(char *cmd, char **envp);
void	ft_free(void **ptr);
t_info	set_info(char *line, char **envp);
void	free_cmds(t_cmds *cmds);
void	ft_free_arr(char ***arr);
char	*make_cmd_redir(char *content);
char	**remove_redir(char **cmd, int start, int end);
int		is_redir(char *c);
void	process_redir(char **cmd, int flag, int index, int mode);
void	redirection(t_cmds *cmds);
void	out_redir(int src, char *outfile, int flag);
void	get_heredoc(char *limiter);
void	in_redir(int dst, char *infile);
int		is_num_str(char *str);

#endif
