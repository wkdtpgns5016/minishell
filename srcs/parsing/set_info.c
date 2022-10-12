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

int	check_syntax(t_info *info, char *line, char **token)
{
	int		flag;

	if (token == 0)
		flag = check_readline(line);
	else
		flag = check_sub_readline(token);
	if (flag != 0)
	{
		if (flag == 1)
		{
			info->recent_exit_code = \
			make_exit_code(&(info->recent_exit_code), 1);
			info->recent_exit_code[0] = 258;
		}
		return (1);
	}
	return (0);
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
			if (line[i] != ' ' && line[i] != '\t')
			{
				info->cmds = new_set_cmds(info, line, i);
				break ;
			}
			i++;
		}
		if (i == length)
			info->cmds = 0;
	}
}
