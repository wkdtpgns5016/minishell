#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	char *str = "a | b | c";
	t_info	info;

	info = set_info(str, envp);
	while (info.cmds != 0)
	{
		printf("%s\n", (info.cmds)->cmd);
		(info.cmds) = (info.cmds)->next;
	}
	free_cmds(info.cmds);
}
