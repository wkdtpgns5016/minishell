#include "../includes/minishell.h"

int	ft_echo(int opt, char *arg)
{
	if (arg)
		printf("%s", arg);
	if (!opt)
		printf("\n");
	return (0);
}

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	printf("%s\n", path);
	return (0);
}

int	ft_env(t_list *envl)
{
	while (envl)
	{
		if (strchr(envl->content, '='))
			printf("%s\n", (char *)envl->content);
		envl = envl->next;
	}
	return (1);
}
