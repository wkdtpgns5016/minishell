/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:45:20 by sehjang           #+#    #+#             */
/*   Updated: 2022/07/20 14:45:20 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipe(t_cmds *cmds, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		cmds = cmds->next;
		i++;
	}
	close(cmds->fd[1]);
	close(cmds->fd[0]);
}

int	find_cmds_index(t_cmds *cmds, pid_t pid)
{
	int	index;

	index = 0;
	while (cmds != 0)
	{
		if (cmds->pid == pid)
			return (index);
		index++;
		cmds = cmds->next;
	}
	return (0);
}

void	wait_child(t_cmds *cmds, int **exit_code)
{
	pid_t	pid;
	int		status;
	int		i;

	status = 0;
	pid = 0;
	i = 0;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		i = find_cmds_index(cmds, pid);
		close_pipe(cmds, i);
		if (is_exit_by_signal(status))
			(*exit_code)[i] = 128 + get_exit_signal_number(status);
		else
			(*exit_code)[i] = get_exit_status(status);
		pid = waitpid(-1, &status, 0);
	}
}
