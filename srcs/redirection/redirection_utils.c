/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:34 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/28 08:52:07 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	is_redir(char *c)
{
	if (*c == '<' && *(c + 1) != '<')
		return (INPUT_REDIR);
	else if (*c == '<' && *(c + 1) == '<')
	{
		if (*(c + 2) != '<')
			return (HERE_DOC_REDIR);
		else
			return (HERE_STRING_REDIR);
	}
	else if (*c == '>' && *(c + 1) != '>')
		return (OUTPUT_TRUNC_REDIR);
	else if (*c == '>' && *(c + 1) == '>')
		return (OUTPUT_APPAND_REDIR);
	return (0);
}

int	get_index_arr(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != 0)
		i++;
	return (i);
}

char	**remove_redir(char **cmd, int start, int end)
{
	char	**new;
	int		len;
	int		remove_num;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = get_index_arr(cmd);
	remove_num = end - start + 1;
	new = (char **)malloc(sizeof(char *) * (len - remove_num + 1));
	while (j < len - remove_num)
	{
		if (i >= start && i <= end)
			i++;
		else
			new[j++] = ft_strdup(cmd[i++]);
	}
	new[j] = 0;
	return (new);
}

int	write_heredoc_file(int fd, char **buffer, char *limiter, t_info *info)
{
	int		size;
	t_list	*buffer_char_list;

	size = 0;
	if (ft_strlen(*buffer) > ft_strlen(limiter))
			size = ft_strlen(*buffer);
	else
		size = ft_strlen(limiter);
	if (ft_strncmp(*buffer, limiter, size) == 0)
		return (0);
	buffer_char_list = char2list(*buffer, info);
	free(*buffer);
	*buffer = list2char(&buffer_char_list);
	write(fd, *buffer, ft_strlen(*buffer));
	write(fd, "\n", 1);
	return (1);
}
