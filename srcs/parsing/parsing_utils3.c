/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:02 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/04 20:44:38 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_signal_flag;

int	get_last_index_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
		i++;
	return (i - 1);
}

int	check_last_pipe(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '|')
		return (1);
	return (0);
}

int	check_null_add(char *add, t_info *info, int backup, t_cursor cursor)
{
	if (add == 0)
	{
		if (g_signal_flag == 2)
		{
			dup2(backup, 0);
			close(backup);
			return (0);
		}
		move_cursor(cursor.col + 2, cursor.row);
		print_error_message("syntax error", "unexpected end of file");
		info->recent_exit_code = make_exit_code(&(info->recent_exit_code), 1);
		info->recent_exit_code[0] = 258;
		return (0);
	}
	return (1);
}

// void	add_last_redir_pipe(char **temp, char **new)
// {
// 	*temp = make_cmd_redir(*new);
// 	ft_free((void **)new);
// 	*new = make_cmd_pipe(*temp);
// 	ft_free((void **)temp);
// }
char	*sum_str_with_space(char *str1, char *str2)
{
	char	*temp;
	char	*new;

	temp = ft_strjoin(" ", str2);
	new = ft_strjoin(str1, temp);
	ft_free((void **)&temp);
	return (new);
}

char	*add_last_cmd(char *str, t_info *info)
{
	char		*temp;
	char		*new;
	char		*add;
	int			backup;
	t_cursor	cursor;

	new = ft_strdup(str);
	g_signal_flag = 1;
	backup = dup(0);
	while (check_last_pipe(new))
	{
		temp = new;
		get_cursor_position(&cursor.col, &cursor.row);
		heredoc_setting();
		add = readline("> ");
		cmd_setting();
		if (check_null_add(add, info, backup, cursor) == 0)
		{
			ft_free((void **)&new);
			return (0);
		}
		new = sum_str_with_space(temp, add);
		ft_free((void **)&add);
		ft_free((void **)&temp);
	}
	return (new);
}
