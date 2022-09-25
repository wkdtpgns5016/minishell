/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:17 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 15:53:51 by sunwchoi         ###   ########.fr       */
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
	{
		ft_free_arr((char ***)cmd);
		return (0);
	}
	(*cmd)[i + 1] = ft_strdup(str2);
	if ((*cmd)[i + 1] == 0)
	{
		ft_free_arr((char ***)cmd);
		return (0);
	}
	return (1);
}

char	**make_heredoc(char *content, t_cmds *cmds)
{
	char	**cmd;
	int		i;

	i = -1;
	cmd = ft_split(content, ' ');
	if (cmd == 0)
		return (0);
	while (cmd[++i] != 0)
	{
		if (g_signal_flag == 2)
			break ;
		if (ft_strncmp(cmd[i], "<<", 2) == 0)
		{
			cmds->heredoc_filepath = get_heredoc(cmd[i + 1]);
			cmds->heredoc_flag = 1;
			if (cmds->heredoc_filepath == 0)
			{
				ft_free_arr((char ***)&cmd);
				return (0);
			}
			if (change_values_arr(&cmd, "<", cmds->heredoc_filepath, i) == 0)
				return (0);
		}
	}
	return (cmd);
}
