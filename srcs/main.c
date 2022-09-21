/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:31 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 10:45:14 by sunwchoi         ###   ########.fr       */
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
	set_terminal();
	get_ev(&info.ev, envp);
	while (1)
	{
		g_signal_flag = 0;
		signal_process_in_waiting();
		line = readline("minishell$ ");
		signal_process_in_command();
		if (!line)
		{
			printf("\033[1A");
			printf("\033[11C");
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
