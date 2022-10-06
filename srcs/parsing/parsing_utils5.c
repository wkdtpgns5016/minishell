/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:17 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/28 07:49:45 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_signal_flag;

int	change_values_arr(char ***cmd, char *str1, char *str2, int i)
{
	ft_free((void **)&(*cmd)[i]);
	ft_free((void **)&(*cmd)[i + 1]);
	(*cmd)[i] = ft_strdup(str1);
	if ((*cmd)[i] == 0)
		return (0);
	(*cmd)[i + 1] = ft_strdup(str2);
	if ((*cmd)[i + 1] == 0)
		return (0);
	return (1);
}

int	sub_make_heredoc(t_cmds *cmds, t_info *info, int index, char ***cmd)
{
	if (g_signal_flag == 2)
		return (1);
	if (ft_strncmp((*cmd)[index], "<<", 2) == 0)
	{
		if (cmds->heredoc_filepath != 0)
			ft_free((void **)&cmds->heredoc_filepath);
		cmds->heredoc_filepath = get_heredoc((*cmd)[index + 1], info);
		cmds->heredoc_flag = 1;
		if (cmds->heredoc_filepath == 0)
			return (-1);
		if (change_values_arr(cmd, "<", cmds->heredoc_filepath, index) == 0)
			return (-1);
	}
	return (0);
}

char	**make_heredoc(char *content, t_cmds *cmds, t_info *info)
{
	char	**cmd;
	int		i;
	int		flag;

	i = -1;
	cmd = ft_split(content, ' ');
	flag = 1;
	if (cmd == 0)
		return (0);
	while (cmd[++i] != 0)
	{
		flag = sub_make_heredoc(cmds, info, i, &cmd);
		if (flag == 1)
			break ;
		else if (flag == -1)
		{
			ft_free_arr((char ***)&cmd);
			return (0);
		}
	}
	return (cmd);
}
