/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:31 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:57:32 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		signal(CTRL_C, main_handler);
		signal(CTRL_SLASH, main_handler);
		line = readline("minishell$ ");
		signal(CTRL_C, sub1_handler);
		signal(CTRL_SLASH, sub1_handler);
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
		free_cmds(&(info.cmds));
		ft_free((void **)&line);
	}
	ret_terminal();
}
