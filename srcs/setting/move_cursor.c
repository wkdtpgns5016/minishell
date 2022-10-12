/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:53:10 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/12 13:12:52 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_putchar_int(int c)
{
	write(1, &c, 1);
	return (0);
}

void	move_cursor_main(int col, int row)
{
	char			*cm;
	char			*temp;
	struct termios	org_term;

	org_term = set_terminal_for_cursor();
	tgetent(NULL, "xterm");
	cm = tgetstr("cm", NULL);
	row--;
	if (col > 11 && !is_end_of_window(row + 1))
		row++;
	temp = tgoto(cm, col, row);
	tputs(temp, 1, ft_putchar_int);
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
}

void	move_cursor(int col, int row)
{
	char			*cm;
	char			*temp;
	struct termios	org_term;

	org_term = set_terminal_for_cursor();
	tgetent(NULL, "xterm");
	cm = tgetstr("cm", NULL);
	if (is_end_of_window(row))
		row--;
	temp = tgoto(cm, col, row);
	tputs(temp, 1, ft_putchar_int);
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
}
