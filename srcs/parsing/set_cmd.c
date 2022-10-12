/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:01:15 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/11 16:01:17 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmds	*new_set_cmds(t_info *info, char *line, int i)
{
	t_cmds	*cmds;
	char	*new_line;
	char	**token;
	char	**temp;

	cmds = 0;
	info->history_cmd = ft_strdup(line);
	if (check_syntax(info, line, 0))
		return (0);
	new_line = add_last_cmd(line, info);
	if (new_line == 0)
		return (0);
	if (info->history_cmd != 0)
		ft_free((void **)&info->history_cmd);
	info->history_cmd = ft_strdup(new_line);
	token = divide_line(ft_strdup(new_line + i));
	ft_free((void **)&new_line);
	temp = token;
	token = divide_token_garbage(temp);
	ft_free_arr((char ***)&temp);
	cmds = insert_cmds(token, info);
	ft_free_arr((char ***)&token);
	interpret_cmds(cmds, info);
	return (cmds);
}
