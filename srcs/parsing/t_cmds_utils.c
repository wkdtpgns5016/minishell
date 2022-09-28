/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmds_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:03:30 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/25 18:03:32 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_signal_flag;

t_cmds	*make_cmd(char *content, t_info *info)
{
	t_cmds	*cmd;

	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (cmd == 0)
		return (0);
	cmd->heredoc_flag = 0;
	cmd->heredoc_filepath = 0;
	cmd->cmd = make_heredoc(content, cmd);
	if (cmd->cmd == 0)
	{
		ft_free((void **)&cmd);
		return (0);
	}
	else
		change_cmd(cmd->cmd, info);
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

t_cmds	*make_cmds(char *new, t_info *info)
{
	t_cmds	*cmd_list;
	char	**cmds;
	int		i;

	cmds = ft_split(new, '|');
	i = 0;
	cmd_list = 0;
	if (cmds == 0)
		return (0);
	while (cmds[i] != 0)
	{
		if (g_signal_flag == 2)
			break ;
		add_cmd_back(&cmd_list, make_cmd(cmds[i], info));
		ft_free((void **)(&(cmds[i])));
		i++;
	}
	ft_free((void **)&cmds);
	return (cmd_list);
}
