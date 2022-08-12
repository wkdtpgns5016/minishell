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
		printf("%s\n", (char *)envl->content);
		envl = envl->next;
	}
	return (1);
}

void	ft_exit(char *arg, int size)
{
	long long	num;
	int			mark;
	char		*cpy;

	if (!arg)
	{
		printf("exit\n");
		exit(0);
	}
	cpy = arg;
	while (9 <= *arg && *arg <= 13)
		arg++;
	if (*arg == '+' || *arg == '-')
	{
		mark = 1;
		if (*(arg++) == '-')
			mark = -1;
	}
	num = 0;
	while ('0' <= *arg && *arg <= '9' && check_num(num, mark, *arg - '0'))
		num = num * 10 + (*(arg++)  - '0');
	while (9 <= *arg && *arg <= 13)
		arg++;
	if (*arg)
	{
		if (size == 1)
			printf("exit\n");
		error_excute("exit", cpy, "numeric argument required", 255);
	}
	printf("exit\n");
	exit(num);
}

int	ft_cd(char *path, t_list *evl)
{
	char	*home;
	char	*new_path;
	int		ret;

	home = NULL;
	ret = 0;
	while (evl)
	{
		if (!memcmp("HOME=", evl->content, 5))
		{
			home = (char *)evl->content;
			break ;
		}
		evl = evl->next;
	}
	if (!path)
		ret = chdir(home + 5);
	else if (*path == '~')
	{
		if (!path[1])
			ret = chdir(home + 5);
		else
		{
			new_path = ft_strjoin(home + 5, path + 1);
			ret = chdir(new_path);
			free(new_path);
		}
	}
	else
		ret = chdir(path);
	if (ret < 0)
	{
		print_error_message_with_token("cd", path, "No such file or directory");
		return (1);
	}
	return (0);
}
