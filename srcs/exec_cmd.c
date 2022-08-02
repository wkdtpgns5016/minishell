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



void	exec_controller(t_cmds *cmds, t_ev *ev, int index)
{
	int	flag;

	redirection(cmds);
	flag = check_builtin(cmds->cmd);
	if (flag > 0)
		exec_builtin(cmds, ev, flag, index);
	else
		exec_another(cmds, ev->evp, index);
}

void	exec_cmd(t_info *info)
{
	int		i;
	t_cmds	*cmds;

	i = 0;
	cmds = info->cmds;
	while (cmds != 0)
	{
		set_info_backup_fd(info);
		exec_controller(cmds, &info->ev, i);
		cmds = cmds->next;
		i++;
	}
}
