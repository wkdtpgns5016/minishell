#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	char *cmd = "lsq";
	execute_cmd(cmd, envp);
}
