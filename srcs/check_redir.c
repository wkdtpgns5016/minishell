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

#include "../includes/minishell.h"

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

int	check_redir_after(char **token_arr, int index)
{
	int	check;

	check = 0;
	if (token_arr[index] == 0)
		return (print_error_message_syntax("newline"));
	if (check == 0)
		check = check_redir_with_char(token_arr, index, "|", "||");
	if (check == 0)
		check = check_redir_with_char(token_arr, index, "<", "<<");
	if (check == 0)
		check = check_redir_with_char(token_arr, index, ">", ">>");
	return (check);
}

int	check_redir(char **token_arr, int i)
{
	if (check_redir_after(token_arr, i + 1))
		return (1);
	return (0);
}
