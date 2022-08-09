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
	char *path;

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
		printf("%s\n",(char *)envl->content);
		envl = envl->next;
	}
	return (1);
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
		error_excute("exit", cpy, "numeric argument required", 255);
	exit(num);
}

int	ft_cd(char *path)
{
	if (!path)
		chdir("/Users/sunwchoi");
	else if (chdir(path) < 0)
	{
		print_error_message_with_token("cd", path, "No such file or directory");
		return (1);
	}
	return (0);
}
