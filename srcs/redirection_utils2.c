/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:41 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:58:41 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	process_redir(char **cmd, int flag, int index)
{
	if (flag == INPUT_REDIR)
		in_redir(0, *(cmd + index + 1));
	else if (flag == HERE_DOC_REDIR)
	{
		get_heredoc(*(cmd + index + 1));
		in_redir(0, "here_doc");
	}
	else if (flag == OUTPUT_TRUNC_REDIR)
		out_redir(1, *(cmd + index + 1), 0);
	else
		out_redir(1, *(cmd + index + 1), 1);
}

void	process_redir_with_num(char **cmd, int flag, int index)
{
	char	*num;

	num = *(cmd + index - 1);
	if (flag == INPUT_REDIR)
		in_redir(ft_atoi(num), *(cmd + index + 1));
	else if (flag == HERE_DOC_REDIR)
	{
		get_heredoc(*(cmd + index + 1));
		in_redir(0, "here_doc");
	}
	else if (flag == OUTPUT_TRUNC_REDIR)
		out_redir(ft_atoi(num), *(cmd + index + 1), 0);
	else
		out_redir(ft_atoi(num), *(cmd + index + 1), 1);
}
