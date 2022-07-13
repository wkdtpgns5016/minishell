/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:31:42 by sehjang           #+#    #+#             */
/*   Updated: 2022/06/17 17:31:43 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_null(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		*s1 = '\0';
	}
	if (!s1 || !s2)
		return (0);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	if (s1)
		while (s1[j] != '\0')
			new[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}

static char	*get_backup(char *backup)
{
	char	*new;
	int		i;
	int		j;

	if (*backup == '\0')
	{
		free(backup);
		return (0);
	}
	i = 0;
	j = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	new = (char *)malloc(sizeof(char) * (ft_strlen(backup) - i + 1));
	if (backup[i] == '\n')
		i++;
	while (backup[i] != '\0')
		new[j++] = backup[i++];
	new[j] = '\0';
	free(backup);
	return (new);
}

static char	*get_line(char *backup)
{
	char	*line;
	int		i;
	int		j;

	if (*backup == '\0')
		return (0);
	i = 0;
	j = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	while (backup[j] && backup[j] != '\n')
	{
		line[j] = backup[j];
		j++;
	}
	if (backup[j] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	int			bytes;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	static char	*backup;

	bytes = 1;
	if (fd < 0)
		return (0);
	while (bytes > 0 && ft_strchr(backup, '\n') == 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(backup);
			return (0);
		}
		buffer[bytes] = '\0';
		backup = ft_strjoin_null(backup, buffer);
	}
	line = get_line(backup);
	backup = get_backup(backup);
	return (line);
}
