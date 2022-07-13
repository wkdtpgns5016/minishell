/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:57:43 by sehjang           #+#    #+#             */
/*   Updated: 2022/03/15 13:57:45 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*arr;

	i = 0;
	arr = (unsigned char *)ptr;
	while (i < num)
	{
		arr[i] = value;
		i++;
	}
	return ((void *)arr);
}
