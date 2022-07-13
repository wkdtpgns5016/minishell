/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:52:51 by sehjang           #+#    #+#             */
/*   Updated: 2022/03/15 13:52:55 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t num)
{
	size_t			i;
	unsigned char	*arr;

	i = 0;
	arr = (unsigned char *)ptr;
	while (i < num)
	{
		arr[i] = 0;
		i++;
	}
}
