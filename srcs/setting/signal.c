/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:27:31 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/04 20:35:31 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

int	g_signal_flag;

void	cmd_handler(int sig)
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

void	heredoc_handler(int sig)
{
	if (sig == CTRL_C)
	{
		printf("\n");
		if (g_signal_flag == 1)
			close(0);
		g_signal_flag = 2;
	}
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
}
