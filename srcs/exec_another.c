#include "../includes/minishell.h"

int	first_process(t_cmds *cmds, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		// ft_error("Fork error", 1);
		return (0);
	if (pid == 0)
	{
		// close(cmds->fd[0]);
		// dup2(cmds->fd[1], 1);
		execute_cmd(cmds->cmd, envp);
	}
	else if (pid > 0)
	{
		// close(cmds->fd[1]);
		// dup2(cmds->fd[0], 0);
		waitpid(pid, 0, 0);
	}
	return (0);
}

int	exec_another(t_cmds *cmds, char **envp, int index)
{
	if (index == 0)
	{
		if (pipe(cmds->fd) == -1)
			// ft_error("Pipe error", 1);
			return (0);
		first_process(cmds, envp);
	}
	else if (cmds->next == 0)
	{
		//last_process(cmds, envp);
		printf("last_process\n");
	}
	else
	{
		//mid_process(cmds, envp);
		printf("mid_process\n");
	}
	return (0);
}
