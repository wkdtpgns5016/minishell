#include "../includes/minishell.h"

void	ft_echo(int opt, char *arg)
{
	printf("%s", arg);
	if (!opt)
		printf("\n");
}

void	ft_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
		return ;
	printf("%s\n", path);
}

void	ft_env(char **envp)
{
	int	idx;

	idx = -1;
	while (envp[++idx])
		printf("%s\n",envp[idx]);
}
/*
void	sort_envp(char **envp)
{
	int	last_idx;
	int	parent;
	int	child

	last_idx = 0;
	while (envp[last_idx])
		last_idx++;
	while (last_idx)
	{
		parent = 1;
		while (parent - 1 <= last_idx)
		{
			child = parent * 2;
			if (child <= last_idx && envp[parent - 1][0] < envp[child - 1][0])
				swap_envp
			else (envp[parent - 1][0] < envp[child * 2][0]
				swap_envp
		}
	}
}
*/
char	**ft_export(char *arg, char **envp)
{
	char **new_envp;
	char	*new_arg;

	/*if (!arg)
	{
		sort_envp(char **envp);
		return (envp);
	}*/
	if (ft_strchr(arg, '='))
		new_envp = plus_envp(arg, envp);
	else
	{
		new_arg = ft_strjoin(arg, "=\'\'")
		new_envp = plus_envp(arg, envp);
		free(envp);
	}
}

