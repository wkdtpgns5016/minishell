/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:47 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/23 12:14:01 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	set_terminal_in_wait(void)
{
	struct termios	new_term;

	tcgetattr(0, &new_term);
	new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_term);
}

struct termios	set_terminal_for_cursor()
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

void	set_terminal_in_cmd(void)
{
	struct termios	new_term;

	tcgetattr(0, &new_term);
	new_term.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &new_term);
}
