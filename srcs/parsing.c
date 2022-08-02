#include "../includes/minishell.h"

t_cmds	*make_cmd(char *content)
{
	t_cmds	*cmd;
	char	*new_cmd;

	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (cmd == 0)
		return (0);
	new_cmd = make_cmd_redir(content);
	cmd->cmd = ft_split(new_cmd, ' ');
	cmd->next = 0;
	cmd->pred = 0;
	ft_free((void **)&new_cmd);
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

void	set_info_backup_fd(t_info *info)
{
	info->backup[0] = dup(0);
	info->backup[0] = dup(1);
}

/*
t_info	set_info(char *line, char **envp)
{
	t_info	info;

	info.cmds = 0;
	info.envp = envp;
	if (line != 0)
		info.cmds = set_cmds(line);
	return (info);
}*/
