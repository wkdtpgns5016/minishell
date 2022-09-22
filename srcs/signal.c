/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:27:31 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 12:27:37 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

int	g_signal_flag;

void	sub1_handler(int sig)
{
	if (sig == CTRL_C)
	{
		printf("\n");
		if (g_signal_flag == 1)
			close(0);
		g_signal_flag = 2;
	}
	else if (sig == CTRL_SLASH && g_signal_flag != 2)
		printf("Quit : 3\n");
}

void	main_handler(int sig)
{
	if (sig == CTRL_C)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == CTRL_SLASH)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_process_in_waiting(void)
{
	signal(CTRL_C, main_handler);
	signal(CTRL_SLASH, SIG_IGN);
}

void	signal_process_in_command(void)
{
	signal(CTRL_C, sub1_handler);
	signal(CTRL_SLASH, sub1_handler);
}
