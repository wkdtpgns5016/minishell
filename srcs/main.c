#include "../includes/minishell.h"

int main()
{
	char	*line;

	set_terminal();
	signal(CTRL_C, handler);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("\033[1A");
        	printf("\033[11C");
			printf("exit\n");
			return (0);
		}
	}
	ret_terminal();
}
