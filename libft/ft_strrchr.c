/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:03:52 by sehjang           #+#    #+#             */
/*   Updated: 2022/03/15 14:03:53 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;
	size_t	len;

	temp = (char *)s;
	len = 0;
	while (*temp != 0)
		temp++;
	while (len++ < ft_strlen(s) + 1)
	{
		if (*temp == (char)c)
			return (temp);
		temp--;
	}
	return (0);
}
