/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:28:48 by sehjang           #+#    #+#             */
/*   Updated: 2022/06/28 17:28:50 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(void **ptr)
{
	if (*ptr != 0)
	{
		free(*ptr);
		*ptr = 0;
	}
}

void	free_cmds(t_cmds *cmds)
{
	t_cmds	*temp;
	t_cmds	*next;

	temp = cmds;
	while (temp != 0)
	{
		next = temp->next;
		ft_free((void **)(&(temp->cmd)));
		ft_free((void **)(&temp));
		temp = next;
	}
}
