/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:03:45 by sehjang           #+#    #+#             */
/*   Updated: 2022/03/15 14:03:46 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == 0)
		return ((char *)big);
	while (*big != 0 && i < len)
	{
		j = 0;
		while (*(big + j) == *(little + j) && j < len)
		{
			j++;
			if (*(little + j) == 0)
				return ((char *)big);
		}
		big++;
		i++;
		if (len < i + ft_strlen(little))
			break ;
	}
	return (0);
}
