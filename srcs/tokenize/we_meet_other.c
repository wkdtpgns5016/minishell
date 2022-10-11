/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_cmd_with_list1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:10 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/05 03:16:57 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_first_node(t_list **first_node)
{
	t_list	*temp;

	temp = *first_node;
	*first_node = (*first_node)->next;
	free(temp->content);
	temp->content = NULL;
	free(temp);
	temp = NULL;
}

char	*we_meet_char(char *cmd, t_list **cmd_char_list)
{
	char	*new_char;
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

char	*we_meet_quotes(char *cmd, t_info *info, t_list **cmd_char_list)
{
	t_list	*quotes;
	int		only_dollar;

	quotes = NULL;
	cmd = we_meet_char(cmd, &quotes);
	only_dollar = 0;
	while (*cmd)
	{
		if (*cmd == '$')
		{
			cmd = we_meet_dollar(cmd, info, &quotes);
			only_dollar++;
		}
		else
			break ;
	}
	if (*cmd == '"' && only_dollar)
	{
		change_first_node(&quotes);
		cmd++;
	}
	ft_lstadd_back(cmd_char_list, quotes);
	return (cmd);
}
