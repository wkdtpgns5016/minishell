/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:56:23 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:56:25 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_redir_after(char **token_arr, int index)
{
	int	check;

	check = 0;
	if (token_arr[index] == 0)
		return (print_error_message_syntax("newline"));
	if (is_include_str(token_arr[index], "|", ft_strlen(token_arr[index])) == 0)
	{
		if (is_include_str(token_arr[index], "||", ft_strlen(token_arr[index])) == 0)
			check = print_error_message_syntax("||");
		else
			check = print_error_message_syntax("|");
	}
	else if (is_include_str(token_arr[index], "<", ft_strlen(token_arr[index])) == 0)
	{
		if (is_include_str(token_arr[index], "<<", ft_strlen(token_arr[index])) == 0)
			check = print_error_message_syntax("<<");
		else
			check = print_error_message_syntax("<");
	}
	else if (is_include_str(token_arr[index], ">", ft_strlen(token_arr[index])) == 0)
	{
		if (is_include_str(token_arr[index], ">>", ft_strlen(token_arr[index])) == 0)
			check = print_error_message_syntax(">>");
		else
			check = print_error_message_syntax(">");
	}
	return (check);
}

int	check_redir(char **token_arr, int i)
{
	if (check_redir_after(token_arr, i + 1))
		return (1);
	return (0);
}
