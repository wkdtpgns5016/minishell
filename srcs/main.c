#include "../includes/minishell.h"
/*
int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_info	info;

	if (ac < 1 || av == 0 || envp == 0)
		exit(1);
	set_terminal();
	signal(CTRL_C, handler);
	signal(CTRL_SLASH, handler);
	get_ev(&info.ev, envp);
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
		 //data parsing 
		set_info(&info, line);
		//command processing 
		exec_cmd(&info);
		add_history(line);
		 //free memmory 
		free_cmds(&(info.cmds));
		ft_free((void **)&line);
	}
	ret_terminal();
}
*/
int main(int ac, char **av, char **envp)
{
	t_ev	ev;

	av[ac] = 0;
	get_ev(&ev, envp);
	ft_export(NULL, &ev);
	printf("\n\n");
	
	ft_export("f", &ev);
	ft_export(NULL, &ev);
	printf("\n\n");

	ft_env(ev.evl);
	printf("\n\n");
	
	ft_unset("f", &ev);
	ft_export(NULL, &ev);	
	printf("\n\n");
}
