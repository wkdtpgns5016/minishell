/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:02:46 by sehjang           #+#    #+#             */
/*   Updated: 2022/03/15 14:02:47 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*arr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	arr = (char *)ft_calloc(sizeof(char), s1_len + s2_len + 1);
	if (arr == 0)
		return (0);
	ft_memcpy(arr, s1, ft_strlen(s1));
	ft_memcpy(arr + s1_len, s2, ft_strlen(s2));
	arr[s1_len + s2_len] = '\0';
	return (arr);
}
