/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:53:10 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/12 13:12:52 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_end_of_window(int row)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	if (row == --ws.ws_row)
		return (1);
	return (0);
}

int	nbr_length_with_atoi(int *nbr, char *buf, int idx)
{
	int	length;
	int	n;

	length = 0;
	n = ft_atoi(&buf[idx]);
	*nbr = n - 1;
	if (n <= 0)
		length++;
	while (n != 0)
	{
		n /= 10;
		length++;
	}	
	return (length);
}

void	get_cursor_position(int *col, int *rows)
{
	int				it_s_row;
	int				idx;
	char			buf[255];
	struct termios	org_term;

	org_term = set_terminal_for_cursor();
	write(0, "\033[6n", 4);
	idx = read(0, buf, 254);
	buf[idx] = '\0';
	it_s_row = 1;
	idx = 0;
	while (buf[idx])
	{
		if (buf[idx] >= '0' && buf[idx] <= '9')
		{
			if (it_s_row)
				idx += nbr_length_with_atoi(rows, buf, idx);
			else
				idx += nbr_length_with_atoi(col, buf, idx);
			it_s_row = 0;
		}
		idx++;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
}
