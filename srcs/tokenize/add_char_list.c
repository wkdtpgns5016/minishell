/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:14:32 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/11 16:14:33 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_quote(t_list **quote)
{
	t_list	*temp;

	if (ft_lstsize(*quote) == 2)
	{
		ft_lstclear(quote, free);
		return ;
	}
	temp = *quote;
	*quote = (*quote)->next;
	ft_free((void **)&temp->content);
	ft_free((void **)&temp);
	temp = *quote;
	while (temp != 0)
	{
		if (temp->next->next == 0)
		{
			ft_free((void **)&temp->next->content);
			ft_free((void **)&temp->next);
			break ;
		}
		temp = temp->next;
	}
}

t_list	*interpret_quote(char **p_cmd, t_info *info)
{
	char	*cmd;
	char	quote;
	t_list	*quote_lst;

	cmd = *p_cmd;
	quote_lst = NULL;
	quote = *cmd;
	ft_lstadd_back_with_dup(&quote_lst, *cmd);
	while (*++cmd)
	{
		ft_lstadd_back_with_dup(&quote_lst, *cmd);
		if (*cmd == quote)
		{
			if (quote == '"')
				interpret_dollar(quote_lst, info);
			delete_quote(&quote_lst);
			cmd++;
			break ;
		}
	}
	*p_cmd = cmd;
	return (quote_lst);
}

t_list	*add_char_list(char *cmd, t_info *info)
{
	t_list	*cmd_lst;

	cmd_lst = NULL;
	while (*cmd)
	{
		if (*cmd == '"' | *cmd == '\'')
			ft_lstadd_back(&cmd_lst, interpret_quote(&cmd, info));
		else
		{
			if (*cmd == '$')
				no_quote_interpret_dollar(&cmd_lst, info, &cmd);
			else
			{
				ft_lstadd_back_with_dup(&cmd_lst, *cmd);
				cmd++;
			}
		}
	}
	return (cmd_lst);
}
