#include "../includes/minishell.h"

void	set_info_backup_fd(t_info *info)
{
	info->backup[0] = dup(0);
	info->backup[1] = dup(1);
}

t_cmds	*make_cmd(char *content, t_info *info)
{
	t_cmds	*cmd;

	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (cmd == 0)
		return (0);
	cmd->cmd = ft_split(content, ' ');
	convert_env(cmd->cmd, info);
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

t_cmds	*set_cmds(t_info *info, char *line)
{
	t_cmds	*cmd_list;
	char	**cmds;
	char	*new;
	int		i;

	cmd_list = 0;
	i = 0;
	new = make_cmd_pipe_amd_redir(line);
	if (new == 0)
		return (0);
	if (check_readline(new))
	{
		info->recent_exit_code = 258;
		return (0);
	}
	cmds = ft_split(new, '|');
	ft_free((void **)&new);
	if (cmds == 0)
		return (0);
	while (cmds[i] != 0)
	{
		add_cmd_back(&cmd_list, make_cmd(cmds[i], info));
		ft_free((void **)(&(cmds[i])));
		i++;
	}
	ft_free((void **)&cmds);
	return (cmd_list);
}

void	set_info(t_info *info, char *line)
{
	info->cmds = 0;
	if (*line != 0)
		info->cmds = set_cmds(info, line);
}
