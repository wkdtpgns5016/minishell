/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:56:23 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:56:25 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redir_with_char(char **token_arr, int index, char *ch1, char *ch2)
{
	int	check;

	check = 0;
	if (is_include_str(token_arr[index], ch1, ft_strlen(token_arr[index])) == 0)
	{
		if (is_include_str(token_arr[index], ch2, \
		ft_strlen(token_arr[index])) == 0)
			check = print_error_message_syntax(ch2);
		else
			check = print_error_message_syntax(ch1);
	}
	return (check);
}

int	check_redir_with_redir(char **token_arr, int index)
{
	int	check;

	check = 0;
	if (is_redir(token_arr[index]) == INPUT_REDIR)
		return (print_error_message_syntax("<"));
	else if (is_redir(token_arr[index]) == HERE_DOC_REDIR)
		return (print_error_message_syntax("<<"));
	else if (is_redir(token_arr[index]) == HERE_STRING_REDIR)
		return (print_error_message_syntax("<<<"));
	else if (is_redir(token_arr[index]) == OUTPUT_TRUNC_REDIR)
		return (print_error_message_syntax(">"));
	else if (is_redir(token_arr[index]) == OUTPUT_APPAND_REDIR)
		return (print_error_message_syntax(">>"));
	return (0);
}

int	check_redir_after(char **token_arr, int index)
{
	int	check;

	check = 0;
	if (token_arr[index] == 0)
		return (print_error_message_syntax("newline"));
	if (check == 0)
		check = check_redir_with_redir(token_arr, index);
	if (check == 0)
		check = check_redir_with_char(token_arr, index, "&", "&&");
	if (check == 0)
		check = check_redir_with_char(token_arr, index, "|", "||");
	return (check);
}

int	check_redir(char **token_arr, int i)
{
	int		index;
	char	*str;

	index = i + 1;
	if (token_arr[index] != 0)
	{
		if (is_redir(token_arr[i]) == INPUT_REDIR || \
		is_redir(token_arr[i]) == OUTPUT_TRUNC_REDIR)
		{
			if (ft_strncmp(token_arr[index], "&", 1) == 0)
			{
				str = \
				ft_substr(token_arr[index], 1, ft_strlen(token_arr[index] - 1));
				ft_free((void **)&token_arr[index]);
				token_arr[index] = str;
			}
		}
	}
	if (check_redir_after(token_arr, index))
		return (1);
	return (0);
}
