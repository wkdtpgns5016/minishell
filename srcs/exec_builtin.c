#include "../includes/minishell.h"

int	exec_builtin(t_cmds *cmds, char **envp, int flag, int index)
{
	if (index == 0)
	{
		//first_builtin(cmds, envp, flag);
		if (envp == 0 || flag == 0)
			return (0);
		printf("first_builtin\n");
	}
	else if (cmds->next == 0)
	{
		//last_builtin(cmds, envp, flag);
		printf("last_builtin\n");
	}
	else
	{
		//mid_builtin(cmds, envp, flag);
		printf("mid_builtin\n");
	}
	return (0);
}
