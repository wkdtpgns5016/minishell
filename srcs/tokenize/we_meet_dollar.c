/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   we_meet_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:53:52 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/06 17:54:21 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

char	*list2dollar(t_list **first_node)
{
	char	*dollar;
	int		idx;

	dollar = (char *)malloc(sizeof(ft_lstsize(*first_node)));
	if (!dollar)
		exit (1);
	idx = 0;
	change_first_node(first_node);
	while (*first_node)
	{
		dollar[idx] = *(char *)((*first_node)->content);
		change_first_node(first_node);
		idx++;
	}
	dollar[idx] = '\0';
	return (dollar);
}

char	*dollar2env(t_list *evl)
{
	char	*evp;

	if (!evl)
		return (ft_strdup(""));
	evp = (char *)evl->content;
	while (*evp && *evp != '=')
		evp++;
	if (*evp)
		return (ft_strdup(++evp));
	else
		return (ft_strdup(""));
}

t_list	*env2node(char *dollar)
{
	t_list	*first_node;

	first_node = NULL;
	while (*dollar)
		dollar = we_meet_char(dollar, &first_node);
	return (first_node);
}

void	change_node(t_list **first_node, t_info *info)
{
	char	*str_dollar;
	t_list	*evl;

	evl = info->ev.evl;
	str_dollar = list2dollar(first_node);
	if (*str_dollar == '?')
	{
		free(str_dollar);
		str_dollar = ft_itoa(*info->recent_exit_code);
	}
	else
	{
		while (evl)
		{
			if (check_envl(evl->content, str_dollar))
				break ;
			evl = evl->next;
		}
		free(str_dollar);
		str_dollar = dollar2env(evl);
	}
	*first_node = env2node(str_dollar);
	free(str_dollar);
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
			if (ft_isalnum(*cmd) || *cmd == '_')
				cmd = we_meet_char(cmd, &dollar);
			else
				break ;
		}
	}
	change_node(&dollar, info);
	ft_lstadd_back(cmd_char_list, dollar);
	return (cmd);
}
