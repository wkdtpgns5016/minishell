#include "../includes/minishell.h"

void	ft_echo(int opt, char *arg)
{
	if (arg)
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

void	ft_env(t_list *envl)
{
	while (envl)
	{
		printf("%s\n",(char *)envl->content);
		envl = envl->next;
	}
}

void	ft_exit(char *arg)
{
	long long num;
	int	mark;
	char	*cpy;

	if (!arg)
		exit(0);
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
	printf("exit\n");
	if (*arg)
	{
		ft_error("exit", cpy, "numeric argument required");
		exit(255);
	}
	exit(num);
}

void	ft_cd(char *path)
{
	if (!path)
		chdir("/Users/sunwchoi");
	else if (chdir(path) < 0)
		ft_error("cd", path, "No such file or directory");
}
