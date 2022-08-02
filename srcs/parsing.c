#include "../includes/minishell.h"

t_cmds	*make_cmd(char *content)
{
	t_cmds	*cmd;

	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (cmd == 0)
		return (0);
	cmd->cmd = ft_split(content, ' ');
	cmd->next = 0;
	cmd->pred = 0;
	return (cmd);
}

void	add_cmd_back(t_cmds **cmds, t_cmds *node)
{
	t_cmds	*temp;

	temp = *cmds;
	if (temp == 0)
		*cmds = node;
	else
	{
		temp = *cmds;
		while (temp->next != 0)
			temp = temp->next;
		temp->next = node;
	}
}

t_cmds	*set_cmds(char *line)
{
	char	**cmds;
	t_cmds	*cmd_list;
	int		i;

	cmd_list = 0;
	i = 0;
	cmds = ft_split(line, '|');
	if (cmds == 0)
		return (0);
	while (cmds[i] != 0)
	{
		add_cmd_back(&cmd_list, make_cmd(cmds[i]));
		ft_free((void **)(&(cmds[i])));
		i++;
	}
	ft_free((void **)&cmds);
	return (cmd_list);
}
/*
t_info	set_info(char *line)
{
	t_info	info;

	info.cmds = set_cmds(line);
	return (info);
}*/
