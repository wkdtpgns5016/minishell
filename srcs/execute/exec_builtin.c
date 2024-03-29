/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:56:48 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/28 08:13:08 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(char **cmd, t_ev *ev, int flag, int size)
{
	int	status;

	status = 0;
	if (flag == 1)
		status = excute_echo(cmd);
	else if (flag == 2)
		status = ft_env(ev->evl);
	else if (flag == 3)
		status = ft_pwd();
	else if (flag == 4)
		status = ft_export(cmd[1], ev);
	else if (flag == 5)
		status = ft_cd(cmd[1]);
	else if (flag == 6)
		ft_exit(cmd[1], size);
	else if (flag == 7)
		ft_unset(cmd[1], ev);
	return (status);
}

int	child_builtin(t_cmds *cmds, t_info *info, t_builtin_info bt_info, int size)
{
	pid_t	pid;
	int		status;

	pid = fork();
	cmds->pid = pid;
	status = 0;
	if (pid == -1)
		error_excute(*(cmds->cmd), 0, "Fork function error", 1);
	if (pid == 0)
	{
		redirection(cmds, info);
		close(cmds->fd[0]);
		dup2(cmds->fd[1], 1);
		status = execute_builtin(cmds->cmd, &info->ev, bt_info.flag, size);
		exit(status);
	}
	else if (pid > 0)
	{
		close(cmds->fd[1]);
		dup2(cmds->fd[0], 0);
		close(cmds->fd[0]);
	}
	return (status);
}

int	last_builtin(t_cmds *cmds, t_info *info, t_builtin_info bt_info, int size)
{
	pid_t	pid;
	int		status;

	pid = fork();
	cmds->pid = pid;
	status = 0;
	if (pid == -1)
		error_excute(*(cmds->cmd), 0, "Fork function error", 1);
	if (pid == 0)
	{
		redirection(cmds, info);
		status = execute_builtin(cmds->cmd, &info->ev, bt_info.flag, size);
		exit(status);
	}
	return (status);
}

int	solo_builtin(t_cmds *cmds, t_info *info, t_builtin_info bt_info, int size)
{
	int	status;

	redirection(cmds, info);
	status = execute_builtin(cmds->cmd, &info->ev, bt_info.flag, size);
	return (status);
}

int	exec_builtin(t_cmds *cmds, t_info *info, int backup[2], int size)
{
	int				status;
	t_builtin_info	builtin_info;

	status = 0;
	builtin_info.flag = check_builtin(cmds->cmd);
	builtin_info.backup[0] = backup[0];
	builtin_info.backup[1] = backup[1];
	if (cmds->next != 0)
	{
		if (pipe(cmds->fd) == -1)
		{
			printf("minishell: %s: Pipe function error\n", *(cmds->cmd));
			exit(1);
		}
		child_builtin(cmds, info, builtin_info, size);
	}
	else
	{
		if (size == 1)
			status = solo_builtin(cmds, info, builtin_info, size);
		else
			status = last_builtin(cmds, info, builtin_info, size);
	}
	return (status);
}
