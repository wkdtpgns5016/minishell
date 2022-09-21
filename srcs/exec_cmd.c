/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:01 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 09:40:13 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_signal_flag;

int	check_builtin(char **cmd)
{
	if (ft_strncmp(*cmd, "echo", ft_strlen(*cmd)) == 0)
		return (1);
	else if (ft_strncmp(*cmd, "env", ft_strlen(*cmd)) == 0)
		return (2);
	else if (ft_strncmp(*cmd, "pwd", ft_strlen(*cmd)) == 0)
		return (3);
	else if (ft_strncmp(*cmd, "export", ft_strlen(*cmd)) == 0)
		return (4);
	else if (ft_strncmp(*cmd, "cd", ft_strlen(*cmd)) == 0)
		return (5);
	else if (ft_strncmp(*cmd, "exit", ft_strlen(*cmd)) == 0)
		return (6);
	else if (ft_strncmp(*cmd, "unset", ft_strlen(*cmd)) == 0)
		return (7);
	return (0);
}

int	exec_controller(t_cmds *cmds, t_ev *ev, int backup[2], int size)
{
	int	status;
	int	flag;

	status = 0;
	flag = check_builtin(cmds->cmd);
	if (flag > 0)
		status = exec_builtin(cmds, ev, backup, size);
	else
		exec_another(cmds, ev->evp);
	return (status);
}

void	exec_after(int backup[2], t_cmds *cmds)
{
	t_cmds	*temp;

	temp = cmds;
	dup2(backup[0], 0);
	dup2(backup[1], 1);
	while (temp != 0)
	{
		if (temp->next == 0)
			break ;
		close(temp->fd[0]);
		close(temp->fd[1]);
		temp = temp->next;
	}
	close(backup[0]);
	close(backup[1]);
	unlink("./here_doc");
}

int	get_size_cmds(t_cmds *cmds)
{
	int	size;

	size = 0;
	while (cmds != 0)
	{
		size++;
		cmds = cmds->next;
	}
	return (size);
}

void	exec_cmd(t_info *info)
{
	t_cmds	*cmds;
	int		size;
	int		*exit_code;

	if (g_signal_flag == 2)
	{
		info->recent_exit_code = make_exit_code(&(info->recent_exit_code), 1);
		info->recent_exit_code[0] = 1;
		return ;
	}
	cmds = info->cmds;
	if (cmds == 0)
		return ;
	set_info_backup_fd(info);
	size = get_size_cmds(cmds);
	exit_code = make_exit_code(&(info->recent_exit_code), size);
	while (cmds != 0)
	{
		exec_controller(cmds, &info->ev, info->backup, size);
		cmds = cmds->next;
	}
	wait_child(info->cmds, &exit_code);
	info->recent_exit_code = exit_code;
	exec_after(info->backup, info->cmds);
}
