/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:45:00 by sehjang           #+#    #+#             */
/*   Updated: 2022/07/20 16:18:08 by sunwchoi         ###   ########.fr       */
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
# include "./builtin_cmd.h"

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
void	exec_cmd(t_info info);
int		exec_builtin(t_cmds *cmds, char **envp, int flag, int index);
char	*get_str_before_redir(char *cmd, char redir);
int		check_num_str(char *str);

#endif
