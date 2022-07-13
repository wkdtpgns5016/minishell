/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:04:09 by sehjang           #+#    #+#             */
/*   Updated: 2022/03/15 14:37:50 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	s_len;
	size_t	size;
	size_t	i;

	s_len = ft_strlen(s);
	if (s_len < start)
	{
		arr = (char *)ft_calloc(1, 1);
		return (arr);
	}
	size = s_len - start;
	if (size > len)
		size = len;
	arr = (char *)ft_calloc(sizeof(char), size + 1);
	if (arr == 0)
		return (0);
	i = 0;
	while (i < size)
	{
		arr[i++] = s[start];
		start++;
	}
	arr[i] = '\0';
	return (arr);
}
