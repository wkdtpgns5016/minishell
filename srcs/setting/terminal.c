/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:47 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/04 20:36:30 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	dont_echo_ctrl_char(void)
{
	struct termios	new_term;

	tcgetattr(0, &new_term);
	new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_term);
}

void	echo_ctrl_char(void)
{
	struct termios	new_term;

	tcgetattr(0, &new_term);
	new_term.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &new_term);
}

struct termios	set_terminal_for_cursor(void)
{
	struct termios	term;
	struct termios	org_term;

	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &org_term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (org_term);
}


