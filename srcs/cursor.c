#include "../includes/minishell.h"
#include <sys/fcntl.h>
#include <term.h>
#include <unistd.h>

int	nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}


void	get_cursor_position(int *col, int *rows)
{
	int		it_s_row;
	int		idx;
	char	buf[255];
	int		ret;
	//int	fd;
	struct termios term;
	struct termios org_term;
	
	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &org_term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	//fd = open("imsi", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(0, "\033[6n" ,4);  //report cursor location
	ret = read(0, buf, 254);
	//close(fd);
	//unlink("imsi");
	buf[ret] = '\0';
	it_s_row = 1;
	idx = 0;
	while (buf[idx])
	{
		if (buf[idx] >= '0' && buf[idx] <= '9')
		{
			if (it_s_row)
				*rows = ft_atoi(&buf[idx]) - 1;
			else
				*col = ft_atoi(&buf[idx]) - 1;
			it_s_row = 0;
			idx += nbr_length(*col + 1) - 1;
		}
		idx++;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	ft_putchar_int(int c)
{
	write(1, &c, 1);
	return (0);
}

void	move_cursor(int *cols, int *rows, int col, int row)
{
	char *cm;
	struct termios term;
	struct termios org_term;

	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &org_term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	tgetent(NULL, "xterm");
	cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, *cols +col, *rows + row), 1, ft_putchar_int);
	set_terminal();
	
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
}
