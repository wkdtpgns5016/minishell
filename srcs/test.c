#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;

	line = "a|a|d|v|e";
	line = make_cmd_pipe(line);
	printf("%s\n", line);
	while (1)
		;
}
