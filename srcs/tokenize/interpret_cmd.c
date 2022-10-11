/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:02:10 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/11 16:02:16 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	ft_lstadd_back_with_dup(t_list **lst, char c)
{
	char	*content;

	content = (char *)malloc(sizeof(char) * 2);
	if (!content)
		exit(1);
	content[0] = c;
	content[1] = 0;
	ft_lstadd_back(lst, ft_lstnew(content));
}

char	*interpret_cmd(char *cmd, t_info *info)
{
	char	*cmd_cpy;
	t_list	*cmd_lst;
	t_list	*cmd_lst_cpy;
	int		i;

	cmd_lst = add_char_list(cmd, info);
	cmd_cpy = (char *)malloc(sizeof(char) * (ft_lstsize(cmd_lst) + 1));
	i = 0;
	cmd_lst_cpy = cmd_lst;
	while (cmd_lst)
	{
		cmd_cpy[i++] = *(char *)cmd_lst->content;
		cmd_lst = cmd_lst->next;
	}
	ft_lstclear(&cmd_lst_cpy, free);
	return (cmd_cpy);
}

void	interpret_cmds(t_cmds *cmds, t_info *info)
{
	int		idx;
	char	*temp;

	while (cmds)
	{
		idx = -1;
		while (cmds->cmd[++idx])
		{
			temp = cmds->cmd[idx];
			cmds->cmd[idx] = interpret_cmd(cmds->cmd[idx], info);
			if (temp != 0)
				ft_free((void **)&temp);
		}
		cmds = cmds->next;
	}
}
