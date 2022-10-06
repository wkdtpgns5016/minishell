/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:56:11 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:56:13 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redir_or_pipe(char *str)
{
	int	flag;

	flag = is_redir(str);
	if (flag)
		return (flag);
	else
	{
		if (*str == '|')
			return (PIPE_LINE);
	}
	return (0);
}

int	check_token(char **token_arr, int i, int flag)
{
	if (flag == PIPE_LINE)
		return (check_pipe(token_arr, i));
	else
		return (check_redir(token_arr, i));
}

int	check_first_token(char *token)
{
	int	check;

	check = 0;
	if (is_include_str(token, "|", ft_strlen(token)) == 0)
	{
		if (is_include_str(token, "||", ft_strlen(token)) == 0)
			check = print_error_message_syntax("||");
		else
			check = print_error_message_syntax("|");
	}
	else if (is_include_str(token, "&", ft_strlen(token)) == 0)
	{
		if (is_include_str(token, "&&", ft_strlen(token)) == 0)
			check = print_error_message_syntax("&&");
		else
			check = print_error_message_syntax("&");
	}
	return (check);
}

int	check_sub_readline(char **token)
{
	int		check;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	check = check_first_token(token[0]);
	while (token[i] != 0)
	{
		if (check)
			break ;
		flag = is_redir_or_pipe(token[i]);
		if (flag)
			check = check_token(token, i, flag);
		i++;
	}
	return (check);
}

int	check_readline(char *line)
{
	char	**token;
	int		check;
	char	*new;

	check = 0;
	if (*line)
	{
		new = make_cmd_pipe_amd_redir(line);
		if (new == 0)
			return (-1);
		token = ft_split(new, ' ');
		if (token == 0)
			return (-1);
		check = check_sub_readline(token);
		ft_free_arr((char ***)&token);
		ft_free((void **)&new);
	}
	return (check);
}
