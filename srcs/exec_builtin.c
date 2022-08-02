#include "../includes/minishell.h"

void	first_builtin(char **cmd, t_ev *ev, int flag)
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

int	exec_builtin(t_cmds *cmds, t_ev *ev, int flag, int index)
{
	if (index == 0)
	{
		first_builtin(cmds->cmd, ev, flag);
		if (ev->evp == 0 || flag == 0)
			return (0);
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
