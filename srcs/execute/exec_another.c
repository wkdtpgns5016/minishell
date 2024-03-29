/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_another.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:56:41 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/28 07:58:01 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process(t_cmds *cmds, char **envp, t_info *info)
{
	pid_t	pid;

	pid = fork();
	cmds->pid = pid;
	if (pid == -1)
		error_excute(*(cmds->cmd), 0, "Fork function error", 1);
	if (pid == 0)
	{
		redirection(cmds, info);
		close(cmds->fd[0]);
		dup2(cmds->fd[1], 1);
		execute_cmd(cmds->cmd, envp);
	}
	else if (pid > 0)
	{
		close(cmds->fd[1]);
		dup2(cmds->fd[0], 0);
		close(cmds->fd[0]);
	}
}

void	last_process(t_cmds *cmds, char **envp, t_info *info)
{
	pid_t	pid;

	pid = fork();
	cmds->pid = pid;
	if (pid == -1)
		error_excute(*(cmds->cmd), 0, "Fork function error", 1);
	if (pid == 0)
	{
		redirection(cmds, info);
		execute_cmd(cmds->cmd, envp);
	}
}

void	exec_another(t_cmds *cmds, char **envp, t_info *info)
{
	if (cmds->next != 0)
	{
		if (pipe(cmds->fd) == -1)
		{
			printf("minishell: %s: Pipe function error\n", *(cmds->cmd));
			exit(1);
		}
		child_process(cmds, envp, info);
	}
	else
		last_process(cmds, envp, info);
}
