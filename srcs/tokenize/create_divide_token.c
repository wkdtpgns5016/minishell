/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_divide_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:03:12 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/11 16:03:12 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**create_divide_token(char *token)
{
	char	**divide_redir;
	char	*temp;

	temp = make_cmd_pipe_amd_redir(token);
	divide_redir = ft_split(temp, ' ');
	ft_free((void **)&temp);
	return (divide_redir);
}
