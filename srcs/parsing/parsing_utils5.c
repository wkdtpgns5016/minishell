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

char	**make_heredoc(char *content)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(content, ' ');
	if (cmd == 0)
		return (0);
	while (cmd[i] != 0)
	{
		if (g_signal_flag == 2)
			break ;
		if (ft_strncmp(cmd[i], "<<", 2) == 0)
		{
			get_heredoc(cmd[i + 1]);
			//ft_free((void **)&cmd[i]);
			//ft_free((void **)&cmd[i + 1]);
			cmd[i] = ft_strdup("<");
			cmd[i + 1] = ft_strdup("here_doc");
		}
		i++;
	}
	i = 0;
	return (cmd);
}
