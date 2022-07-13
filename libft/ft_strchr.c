/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:58:45 by sehjang           #+#    #+#             */
/*   Updated: 2022/03/15 13:58:46 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*temp;

	temp = (char *)s;
	while (*temp != 0)
	{
		if (*temp == (unsigned char)c)
			return (temp);
		temp++;
	}
	if (c == '\0')
		return (temp);
	return (0);
}
