/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:41 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/28 07:52:33 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_num_str(char *str)
{
	while (*str != 0)
	{
		if (ft_isdigit(*str))
			continue ;
		else
			return (0);
	}
	return (1);
}

void	process_redir(char **cmd, int flag, int index, t_cmds *cmds, t_info *info)
{
	if (flag == INPUT_REDIR)
		in_redir(0, *(cmd + index + 1), cmds->heredoc_flag);
	else if (flag == HERE_DOC_REDIR)
	{
		get_heredoc(*(cmd + index + 1), info);
		in_redir(0, cmds->heredoc_filepath, cmds->heredoc_flag);
	}
	else if (flag == OUTPUT_TRUNC_REDIR)
		out_redir(1, *(cmd + index + 1), 0);
	else
		out_redir(1, *(cmd + index + 1), 1);
}
