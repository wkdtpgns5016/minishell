#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_info	info;

	if (ac < 1 || av == 0 || envp == 0)
		exit(1);
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
		/* data parsing */
		info = set_info(line, envp);

		/* command processing */

		/* free memmory */
		free_cmds(info.cmds);
		ft_free((void **)&line);
	}
	ret_terminal();
}
