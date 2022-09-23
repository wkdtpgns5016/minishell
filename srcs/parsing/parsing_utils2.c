/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:57 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:57:58 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_info_backup_fd(t_info *info)
{
	info->backup[0] = dup(0);
	info->backup[1] = dup(1);
}

int	get_index_pipe(char *temp, int index)
{
	int	i;

	i = index;
	while (*(temp + i) != '\0')
	{
		if (*(temp + i) == '|')
		{
			if (*(temp + i + 1) != '|')
				break ;
			else
				i++;
		}
		i++;
	}
	if (i == (int)ft_strlen(temp))
		return (-1);
	return (i);
}

char	*add_str_between_pipe(char *str, char *add)
{
	char	*temp;
	char	*new;

	temp = ft_strjoin(str, add);
	if (temp == 0)
		return (0);
	new = ft_strjoin(temp, " | ");
	if (new == 0)
		return (0);
	ft_free((void **)&temp);
	return (new);
}

void	sub_cmd_pipe(char *content, int *j, char **cmd)
{
	int		i;
	char	*new;
	char	*temp;

	while (*j < (int)ft_strlen(content))
	{
		temp = *cmd;
		i = get_index_pipe(content, *j);
		if (i < 0)
			break ;
		new = ft_substr(content, *j, i - *j);
		*cmd = add_str_between_pipe(temp, new);
		ft_free((void **)&temp);
		ft_free((void **)&new);
		*j = i + 1;
	}
	temp = *cmd;
	*cmd = ft_strjoin(temp, content + *j);
	ft_free((void **)&temp);
}

char	*make_cmd_pipe(char *content)
{
	char	*cmd;
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = get_index_pipe(content, j);
	if (i < 0)
		return (ft_strdup(content));
	new = ft_substr(content, j, i - j);
	cmd = add_str_between_pipe("", new);
	ft_free((void **)&new);
	j = i + 1;
	sub_cmd_pipe(content, &j, &cmd);
	return (cmd);
}
