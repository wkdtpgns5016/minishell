#include "../includes/minishell.h"

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

	flag = check_builtin(cmds->cmd);
	if (flag > 0)
		status = exec_builtin(cmds, ev, backup, size);
	else
		status = exec_another(cmds, ev->evp);
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
		(*exit_code)[i] = get_exit_status(status);
		pid = waitpid(-1, &status, 0);
	}
}

void	exec_cmd(t_info *info)
{
	t_cmds	*cmds;
	int		size;
	int		*exit_code;

	cmds = info->cmds;
	if (cmds == 0)
		return ;
	set_info_backup_fd(info);
	size = get_size_cmds(cmds);
	if (info->recent_exit_code != 0)
		ft_free((void **)&info->recent_exit_code);
	exit_code = (int *)malloc(sizeof(int) * (size + 1));
	while (cmds != 0)
	{
		exec_controller(cmds, &info->ev, info->backup, size);
		cmds = cmds->next;
	}
	wait_child(info->cmds, &exit_code);
	exit_code[size] = -1;
	info->recent_exit_code = exit_code;
	exec_after(info->backup, info->cmds);
	int i = 0;
	while (i < size)
	{
		printf("%d ", info->recent_exit_code[i++]);
	}
	printf("\n");
}
