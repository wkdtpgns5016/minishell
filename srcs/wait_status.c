#include "../includes/minishell.h"

int	get_exit_status(int status)
{
	return (((status) & 0xff00) >> 8);
}

int	is_exit_by_signal(int status)
{
	return (((signed char)(((status) & 0x7f) + 1) >> 1) > 0);
}

int	get_exit_signal_number(int status)
{
	return ((status) & 0x7f);
}
