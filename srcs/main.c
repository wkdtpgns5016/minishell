/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:31 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 17:41:37 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_signal_flag;

int	loop_minishell(t_info info)
{
	char		*line;
	t_cursor	cursor;

	while (1)
	{
		g_signal_flag = 0;
		signal_process_in_waiting();
		get_cursor_position(&cursor.col, &cursor.row);
		line = readline("minishell$ ");
		signal_process_in_command();
		if (!line)
		{
			move_cursor(cursor.col + 11, cursor.row -1);
			printf("exit\n");
			return (0);
		}
		set_info(&info, line);
		exec_cmd(&info);
		add_history(line);
		unlink("./here_doc");
		free_cmds(&(info.cmds));
		ft_free((void **)&line);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_info	info;

	if (ac < 1 || av == 0 || envp == 0)
		exit(1);
	if (!setting(&info, envp))
		return (1);
	if (ac < 1 || av == 0 || envp == 0)
	{
		ft_putstr_fd("minishell: argument error", 2);
		exit(1);
	}
	set_terminal();
	loop_minishell(info);
	ret_terminal();
	return (0);
}
