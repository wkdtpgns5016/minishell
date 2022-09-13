#include "../includes/minishell.h"

int	get_exit_status(int status)
{
	return (((status) & 0xff00) >> 8);
}

int	child_process(t_cmds *cmds, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == -1)
		error_excute(*(cmds->cmd), 0, "Fork function error", 1);
	if (pid == 0)
	{
		redirection(cmds);
		close(cmds->fd[0]);
		dup2(cmds->fd[1], 1);
		execute_cmd(cmds->cmd, envp);
	}
	else if (pid > 0)
	{
		close(cmds->fd[1]);
		dup2(cmds->fd[0], 0);
		waitpid(pid, &status, WNOWAIT);
	}
	return (get_exit_status(status));
}

int	last_process(t_cmds *cmds, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	status = 0;
	if (pid == -1)
		error_excute(*(cmds->cmd), 0, "Fork function error", 1);
	if (pid == 0)
	{
		redirection(cmds);
		execute_cmd(cmds->cmd, envp);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	return (get_exit_status(status));
}

int	exec_another(t_cmds *cmds, char **envp)
{
	int	status;

	status = 0;
	if (pipe(cmds->fd) == -1)
	{
		printf("minishell: %s: Pipe function error\n", *(cmds->cmd));
		return (1);
	}
	if (cmds->next != 0)
		status = child_process(cmds, envp);
	else
		status = last_process(cmds, envp);
	return (status);
}
