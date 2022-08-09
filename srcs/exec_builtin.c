#include "../includes/minishell.h"

int	execute_builtin(char **cmd, t_ev *ev, int flag)
{
	int	status;

	status = 0;
	if (flag == 1)
		status = ft_echo(0, cmd[1]);
	else if (flag == 2)
		status = ft_env(ev->evl);
	else if (flag == 3)
		status = ft_pwd();
	else if (flag == 4)
		status = ft_export(cmd[1], ev);
	else if (flag == 5)
		status = ft_cd(cmd[1], ev->evl);
	else if (flag == 6)
		ft_exit(cmd[1]);
	else if (flag == 7)
		ft_unset(cmd[1], ev);
	return (status);
}

int	child_builtin(t_cmds *cmds, t_ev *ev, int flag, int backup[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_excute(*(cmds->cmd), 0, "Fork function error", 1);
	if (pid == 0)
	{
		redirection(cmds, backup);
		close(cmds->fd[0]);
		dup2(cmds->fd[1], 1);
		execute_builtin(cmds->cmd, ev, flag);
	}
	else if (pid > 0)
	{
		close(cmds->fd[1]);
		dup2(cmds->fd[0], 0);
		waitpid(pid, 0, 0);
	}
	return (0);
}

int	last_builtin(t_cmds *cmds, t_ev *ev, int flag, int backup[2])
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == -1)
		error_excute(*(cmds->cmd), 0, "Fork function error", 1);
	if (pid == 0)
	{
		redirection(cmds, backup);
		execute_builtin(cmds->cmd, ev, flag);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	return (get_exit_status(status));
}

int	solo_builtin(t_cmds *cmds, t_ev *ev, int flag, int backup[2])
{
	int	status;

	redirection(cmds, backup);
	status = execute_builtin(cmds->cmd, ev, flag);
	return (status);
}

int	exec_builtin(t_cmds *cmds, t_ev *ev, int backup[2], int size)
{
	int	status;
	int	flag;

	status = 0;
	flag = check_builtin(cmds->cmd);
	if (pipe(cmds->fd) == -1)
	{
		printf("minishell: %s: Pipe function error\n", *(cmds->cmd));
		return (1);
	}
	if (cmds->next != 0)
		child_builtin(cmds, ev, flag, backup);
	else
	{
		if (size == 1)
			status = solo_builtin(cmds, ev, flag, backup);
		else
			status = last_builtin(cmds, ev, flag, backup);
	}
	return (status);
}
