/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:31 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/04 20:42:13 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

extern int	g_signal_flag;

void	get_ev(t_ev *ev, char **envp)
{
	int		idx;
	t_list	*new;
	char	*content;
	char	**p;

	idx = 0;
	while (envp[idx])
		idx++;
	p = (char **)malloc(sizeof(char *) * (idx + 2));
	if (!p)
		exit(1);
	p[0] = NULL;
	p[idx + 1] = NULL;
	ev->evl = NULL;
	idx = -1;
	while (envp[++idx])
	{
		content = ft_strdup(envp[idx]);
		new = ft_lstnew(content);
		ft_lstadd_back(&(ev->evl), new);
		p[idx + 1] = content;
	}
	sort_s(p, idx - 1);
	ev->evp = p;
}

int	loop_minishell(t_info info)
{
	char		*line;
	t_cursor	cursor;

	while (1)
	{
		g_signal_flag = 0;
		get_cursor_position(&cursor.col, &cursor.row);
		main_setting();
		line = readline("minishell$ ");
		cmd_setting();
		if (!line)
		{
			move_cursor(cursor.col + 11, cursor.row);
			printf("exit\n");
			return (0);
		}
		set_info(&info, line);
		exec_cmd(&info);
		if (info.history_cmd != 0)
			add_history(info.history_cmd);
		free_cmds(&(info.cmds));
		ft_free((void **)&line);
		ft_free((void **)&(info.history_cmd));
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_info	info;

	if (ac < 1 || av == 0 || envp == 0)
		exit(1);
	if (ac < 1 || av == 0 || envp == 0)
	{
		ft_putstr_fd("minishell: argument error", 2);
		exit(1);
	}
	get_ev(&info.ev, envp);
	info.recent_exit_code = make_exit_code(&(info.recent_exit_code), 1);
	info.recent_exit_code[0] = 0;
	loop_minishell(info);
	return (0);
}
