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

void	ft_free_arr(char ***arr)
{
	int	i;

	i = 0;
	if (*arr != 0)
	{
		while ((*arr)[i] != 0)
		{
			if ((*arr)[i] != 0)
				ft_free((void *)&((*arr)[i]));
			i++;
		}
		ft_free((void *)arr);
	}
}
