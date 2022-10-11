/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:54:09 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/06 17:54:10 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*list2char(t_list **first_node)
{
	char	*dollar;
	int		idx;

	dollar = (char *)malloc(sizeof(char) * ft_lstsize(*first_node) + 1);
	if (!dollar)
		exit (1);
	idx = 0;
	while (*first_node)
	{
		dollar[idx] = *(char *)((*first_node)->content);
		change_first_node(first_node);
		idx++;
	}
	dollar[idx] = '\0';
	return (dollar);
}

t_list	*char2list(char *cmd, t_info *info)
{
	t_list	*cmd_char_list;

	cmd_char_list = NULL;
	while (*cmd)
	{
		if (*cmd == '$')
			cmd = we_meet_dollar(cmd, info, &cmd_char_list);
		else if (*cmd == '"')
			cmd = we_meet_quotes(cmd, info, &cmd_char_list);
		else
			cmd = we_meet_char(cmd, &cmd_char_list);
	}
	return (cmd_char_list);
}

void	change_line(char **line, t_info *info)
{
	t_list	*line_char_list;

	line_char_list = char2list(*line, info);
	free(*line);
	*line = list2char(&line_char_list);
}
