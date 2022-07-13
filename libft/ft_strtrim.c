/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:04:00 by sehjang           #+#    #+#             */
/*   Updated: 2022/03/15 14:04:03 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	head;
	size_t	tail;
	char	*arr;

	head = 0;
	tail = ft_strlen(s1);
	while (s1[head] != 0 && ft_strchr(set, s1[head]) != 0)
		head++;
	if (head < tail)
	{
		while (s1[tail - 1] != 0 && ft_strchr(set, s1[tail]) != 0)
			tail--;
	}
	arr = (char *)ft_calloc(sizeof(char), tail - head + 2);
	if (arr == 0)
		return (0);
	ft_strlcpy(arr, s1 + head, tail - head + 2);
	return (arr);
}
