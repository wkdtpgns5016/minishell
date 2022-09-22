/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:31 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 17:41:37 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_signal_flag;

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_info	info;
	t_cursor cursor;

	if (ac < 1 || av == 0 || envp == 0)
		exit(1);
	if (!setting(&info, envp))
		return (1);
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
	ret_terminal();
}
