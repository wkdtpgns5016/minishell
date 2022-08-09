#include "../includes/minishell.h"

void	execute_builtin(char **cmd, t_ev *ev, int flag)
{
	if (flag == 1)
		ft_echo(0, cmd[1]);
	else if (flag == 2)
		ft_env(ev->evl);
	else if (flag == 3)
		ft_pwd();
	else if (flag == 4)
		ft_export(cmd[1], ev);
	else if (flag == 5)
		ft_cd(cmd[1]);
	else if (flag == 6)
		ft_exit(cmd[1]);
	//else if (flag == 7)
		//ft_unset(cmd[1], ev);
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

int	exec_builtin(t_cmds *cmds, t_ev *ev, int flag, int backup[2])
{
	int	status;

	status = 0;
	if (pipe(cmds->fd) == -1)
	{
		printf("minishell: %s: Pipe function error\n", *(cmds->cmd));
		return (1);
	}
	if (cmds->next != 0)
		child_builtin(cmds, ev, flag, backup);
	else
		status = last_builtin(cmds, ev, flag, backup);
	return (status);
}
