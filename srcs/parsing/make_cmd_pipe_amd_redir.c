/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_pipe_amd_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:51 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:57:52 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_index_redir(char *temp, int index)
{
	int	i;

	i = index;
	while (*(temp + i) != '\0')
	{
		if (is_redir(temp + i))
			break ;
		i++;
	}
	if (i == (int)ft_strlen(temp))
		return (-1);
	return (i);
}

char	*add_str_between_space(char	*str, char *new, int redir)
{
	char	*result;
	char	*temp;

	temp = str;
	result = ft_strjoin(temp, new);
	temp = result;
	if (redir == INPUT_REDIR)
		result = ft_strjoin(temp, " < ");
	if (redir == HERE_DOC_REDIR)
		result = ft_strjoin(temp, " << ");
	if (redir == OUTPUT_TRUNC_REDIR)
		result = ft_strjoin(temp, " > ");
	if (redir == OUTPUT_APPAND_REDIR)
		result = ft_strjoin(temp, " >> ");
	if (redir == HERE_STRING_REDIR)
		result = ft_strjoin(temp, " <<< ");
	ft_free((void **)&temp);
	return (result);
}

char	*sub_make_cmd(char *cmd, char *content, int *i, int *j)
{
	char	*str;
	char	*temp;
	char	*new;

	str = cmd;
	while (*j < (int)ft_strlen(content))
	{
		*i = get_index_redir(content, *j);
		if (*i < 0)
			break ;
		temp = str;
		new = ft_substr(content, *j, *i - *j);
		str = add_str_between_space(temp, new, is_redir(content + *i));
		ft_free((void **)&temp);
		ft_free((void **)&new);
		if (is_redir(content + *i) == HERE_DOC_REDIR || \
		is_redir(content + *i) == OUTPUT_APPAND_REDIR)
			*j = *i + 2;
		else if (is_redir(content + *i) == HERE_STRING_REDIR)
			*j = *i + 3;
		else
			*j = *i + 1;
	}
	return (str);
}

char	*make_cmd_redir(char *content)
{
	char	*cmd;
	char	*temp;
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = get_index_redir(content, j);
	if (i < 0)
		return (ft_strdup(content));
	new = ft_substr(content, j, i - j);
	cmd = add_str_between_space("", new, is_redir(content + i));
	ft_free((void **)&new);
	if (is_redir(content + i) == HERE_DOC_REDIR || \
	is_redir(content + i) == OUTPUT_APPAND_REDIR)
		j = i + 2;
	else if (is_redir(content + i) == HERE_STRING_REDIR)
		j = i + 3;
	else
		j = i + 1;
	cmd = sub_make_cmd(cmd, content, &i, &j);
	temp = cmd;
	cmd = ft_strjoin(temp, content + j);
	ft_free((void **)&temp);
	return (cmd);
}

char	*make_cmd_pipe_amd_redir(char *line)
{
	char	*temp;
	char	*new;

	temp = make_cmd_redir(line);
	new = make_cmd_pipe(temp);
	ft_free((void **)&temp);
	return (new);
}
