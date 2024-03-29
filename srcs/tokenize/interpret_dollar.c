/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:01:54 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/11 16:01:54 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

t_list	*separate_dollar(t_list *now)
{
	char	c;
	t_list	*prev;
	t_list	*next;

	prev = now;
	now = now->next;
	while (now)
	{
		c = *(char *)now->content;
		if (c == '?')
		{
			prev = now;
			now = now->next;
			break ;
		}
		else if (!(ft_isalnum(c) || c == '_'))
			break ;
		prev = now;
		now = now->next;
	}	
	prev->next = NULL;
	next = now;
	return (next);
}

void	no_quote_interpret_dollar(t_list **cmd_lst, t_info *info, char **cmd)
{
	t_list	*dollar;

	dollar = NULL;
	ft_lstadd_back_with_dup(&dollar, **cmd);
	(*cmd)++;
	while (**cmd)
	{
		if (!(ft_isalnum(**cmd) || **cmd == '_'))
		{
			if (**cmd == '?')
			{
				ft_lstadd_back_with_dup(&dollar, **cmd);
				(*cmd)++;
			}
			break ;
		}
		else
			ft_lstadd_back_with_dup(&dollar, **cmd);
		(*cmd)++;
	}
	change_node(&dollar, info);
	ft_lstadd_back(cmd_lst, dollar);
}

t_list	*new_dollar2env(t_list *dollar, t_info *info)
{
	t_list	*next;
	t_list	*last;

	next = separate_dollar(dollar);
	change_node(&dollar, info);
	last = ft_lstlast(dollar);
	if (last)
		last->next = next;
	else
		dollar = next;
	return (dollar);
}

void	interpret_dollar(t_list *quote_lst, t_info *info)
{
	t_list	*prev;
	char	c;

	prev = NULL;
	c = 0;
	while (quote_lst)
	{
		c = *(char *)(quote_lst)->content;
		while (c == '$')
		{
			prev->next = new_dollar2env(quote_lst, info);
			(quote_lst) = prev->next;
			c = *(char *)(quote_lst)->content;
		}
		prev = quote_lst;
		(quote_lst) = (quote_lst)->next;
	}
}
