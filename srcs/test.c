#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	char *line = "<< eof > c";
	t_info info = set_info(line, envp);

	redirection(info.cmds);
}
