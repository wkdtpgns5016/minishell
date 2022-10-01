/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_cmd_with_list1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:10 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/28 07:20:52 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

char	*we_meet_char(char *cmd, t_list **cmd_char_list)
{
	char *new_char;
	t_list	*new_node;

	new_char = (char *)malloc(sizeof(char) * 2);
	if (!new_char)
		exit(1);
	new_char[0] = *cmd;
	new_char[1] = '\0';
	new_node = ft_lstnew(new_char);
	if (!new_char)
		exit(1);
	ft_lstadd_back(cmd_char_list, new_node);
	cmd++;
	return (cmd);
}

void	change_first_node(t_list **first_node)
{
	t_list *temp;

	temp = *first_node;
	*first_node = (*first_node)->next;
	free(temp->content);
	temp->content = NULL;
	free(temp);
	temp = NULL;
}

char	*we_meet_quotes(char *cmd, t_info *info, t_list **cmd_char_list)
{
	int	dollar_is_here;
	t_list	*quotes;

	dollar_is_here = 0;
	quotes = NULL;
	cmd = we_meet_char(cmd, &quotes);
	while (*cmd)
	{
		if (*cmd == '$')
		{
			cmd = we_meet_dollar(cmd, info, &quotes);
			dollar_is_here++;
		}
		else if(*cmd == '"')
		{
			if (!dollar_is_here)
				cmd = we_meet_char(cmd, &quotes);
			break;
		}
		else
			cmd = we_meet_char(cmd, &quotes);
	}
	if (dollar_is_here && *cmd == '"')
	{
		change_first_node(&quotes);
		cmd++;
	}
	ft_lstadd_back(cmd_char_list, quotes);
	return (cmd);
}

char	*we_meet_dollar(char *cmd, t_info *info, t_list **cmd_char_list)
{
	t_list	*dollar;

	dollar = NULL;
	cmd = we_meet_char(cmd, &dollar);
	if (*cmd == '?')
		cmd = we_meet_char(cmd, &dollar);
	else
	{
		while (*cmd)
		{
			if(ft_isalnum(*cmd) || *cmd == '_')
				cmd = we_meet_char(cmd, &dollar);
			else
				break ;
		}
	}
	change_node(&dollar, info);
	ft_lstadd_back(cmd_char_list, dollar);
	return (cmd);
}

t_list *char2list(char *cmd, t_info *info)
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

void	change_line(char **line, t_info *info)
{
	t_list	*line_char_list;

	line_char_list = char2list(*line, info);
	free(*line);
	*line = list2char(&line_char_list);
}
