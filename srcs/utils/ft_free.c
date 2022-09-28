/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:28:48 by sehjang           #+#    #+#             */
/*   Updated: 2022/06/28 17:28:50 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(void **ptr)
{
	if (*ptr != 0)
	{
		free(*ptr);
		*ptr = 0;
	}
}

void	ft_free_arr(char ***arr)
{
	int	i;

	i = 0;
	if (*arr != 0)
	{
		while ((*arr)[i] != 0)
		{
			if ((*arr)[i] != 0)
				ft_free((void **)&((*arr)[i]));
			i++;
		}
		ft_free((void **)arr);
	}
}

void	free_cmds(t_cmds **cmds)
{
	t_cmds	*temp;
	t_cmds	*next;

	temp = *cmds;
	while (temp != 0)
	{
		next = temp->next;
		if (temp->heredoc_flag)
			ft_free((void **)&(temp->heredoc_filepath));
		ft_free_arr((char ***)(&(temp->cmd)));
		ft_free((void **)(&temp));
		temp = next;
	}
}
