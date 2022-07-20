#include "../includes/minishell.h"

void	handler(int sig)
{
	if (sig == CTRL_C)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_terminal()
{
	struct termios new_term;

	tcgetattr(0, &new_term);
	new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_term);

}

void	ret_terminal()
{
	struct termios new_term;

	tcgetattr(0, &new_term);
	new_term.c_lflag &= ECHOCTL;
	tcsetattr(0, TCSANOW, &new_term);

}
