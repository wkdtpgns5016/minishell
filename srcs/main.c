/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:31 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 14:10:01 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_signal_flag;

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_info	info;

	if (ac < 1 || av == 0 || envp == 0)
		exit(1);
	if (!setting(&info, envp))
		return (1);
	while (1)
	{
		g_signal_flag = 0;
		signal_process_in_waiting();
		get_cursor_position(info.cursor_col, info.cursor_row);
		line = readline("minishell$ ");
		signal_process_in_command();
		if (!line)
		{
			move_cursor(info.cursor_col, info.cursor_row, 11, -1);
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
