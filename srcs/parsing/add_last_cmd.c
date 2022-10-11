/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_last_cmd.c   	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:02 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/04 21:21:48 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

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
			return (1);
		}
		move_cursor(cursor.col + 2, cursor.row);
		print_error_message("syntax error", "unexpected end of file");
		info->recent_exit_code = make_exit_code(&(info->recent_exit_code), 1);
		info->recent_exit_code[0] = 258;
		return (1);
	}
	return (0);
}

int	sub_last_cmd(char **new, char **add, t_info *info)
{
	char	*temp;
	char	*temp1;

	if (**add)
	{
		temp1 = *new;
		temp = ft_strjoin(" ", *add);
		*new = ft_strjoin(temp1, temp);
		ft_free((void **)&temp);
		ft_free((void **)&temp1);
	}
	if (check_syntax(info, *add, 0))
	{
		if (info->history_cmd != 0)
			ft_free((void **)&info->history_cmd);
		info->history_cmd = ft_strdup(*new);
		ft_free((void **)add);
		ft_free((void **)new);
		return (1);
	}
	return (0);
}

char	*add_last_cmd(char *str, t_info *info)
{
	char		*new;
	char		*add;
	int			backup;
	t_cursor	cursor;

	new = ft_strdup(str);
	g_signal_flag = 1;
	backup = dup(0);
	while (check_last_pipe(new))
	{
		get_cursor_position(&cursor.col, &cursor.row);
		heredoc_setting();
		add = readline("> ");
		cmd_setting();
		if (check_null_add(add, info, backup, cursor))
		{
			ft_free((void **)&new);
			return (0);
		}
		if (sub_last_cmd(&new, &add, info))
			return (0);
		ft_free((void **)&add);
	}
	return (new);
}
