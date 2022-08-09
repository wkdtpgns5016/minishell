#include "../includes/minishell.h"

int	check_builtin(char **cmd)
{
	if (ft_strncmp(*cmd, "echo", ft_strlen(*cmd)) == 0)
	{
		//if (ft_strncmp(*(cmd + 1), "-n", ft_strlen(*cmd)) == 0)
			return (1);
	}
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

int	exec_controller(t_cmds *cmds, t_ev *ev, int backup[2])
{
	int	status;
	int	flag;

	flag = check_builtin(cmds->cmd);
	if (flag > 0)
		status = exec_builtin(cmds, ev, flag, backup);
	else
		status = exec_another(cmds, ev->evp, backup);
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
		close(temp->fd[0]);
		close(temp->fd[1]);
		temp = temp->next;
	}
}

void	exec_cmd(t_info *info)
{
	t_cmds	*cmds;

	cmds = info->cmds;
	if (cmds == 0)
		return ;
	while (cmds != 0)
	{
		set_info_backup_fd(info);
		info->recent_exit_code = exec_controller(cmds, &info->ev, info->backup);
		unlink("./here_doc");
		cmds = cmds->next;
	}
	exec_after(info->backup, info->cmds);
}
