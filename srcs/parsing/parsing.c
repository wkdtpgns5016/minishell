/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:37 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/28 07:53:31 by sunwchoi         ###   ########.fr       */
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
	cmd->cmd = make_heredoc(content, info);
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

int	check_head_pipe(t_info *info, char *line)
{
	int		i;
	char	**word;

	i = 0;
	word = ft_split(line, ' ');
	if (word == 0)
		return (0);
	while (word[i] != 0)
		i++;
	if (i == 1 && ft_strncmp(*word, "|", 1) == 0)
	{
		print_error_message_syntax("|");
		info->recent_exit_code = make_exit_code(&(info->recent_exit_code), 1);
		info->recent_exit_code[0] = 258;
		ft_free_arr(&word);
		return (1);
	}
	ft_free_arr(&word);
	return (0);
}

t_cmds	*set_cmds(t_info *info, char *line)
{
	t_cmds	*cmd_list;
	char	*new;
	int		flag;

	info->history_cmd = ft_strdup(line);
	if (check_head_pipe(info, line))
		return (0);
	flag = check_readline(line);
	if (flag != 0)
	{
		if (flag == 1)
		{
			info->recent_exit_code = \
			make_exit_code(&(info->recent_exit_code), 1);
			info->recent_exit_code[0] = 258;
		}
		return (0);
	}
	new = add_last_cmd(line, info);
	if (new == 0)
		return (0);
	ft_free((void **)&(info->history_cmd));
	info->history_cmd = ft_strdup(new);
	cmd_list = make_cmds(new, info);
	ft_free((void **)&new);
	return (cmd_list);
}

void	set_info(t_info *info, char *line)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	info->cmds = 0;
	if (*line != 0)
	{
		length = ft_strlen(line);
		while (i < length)
		{
			if (line[i] != ' ')
			{
				info->cmds = set_cmds(info, line);
				break ;
			}
			i++;
		}
		if (i == length)
			info->cmds = 0;
	}
}
