/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:41 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 15:45:09 by sunwchoi         ###   ########.fr       */
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

void	process_redir(char **cmd, int flag, int index, int heredoc_flag)
{
	if (flag == INPUT_REDIR)
		in_redir(0, *(cmd + index + 1), heredoc_flag);
	else if (flag == OUTPUT_TRUNC_REDIR)
		out_redir(1, *(cmd + index + 1), 0);
	else
		out_redir(1, *(cmd + index + 1), 1);
}
