/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:55:04 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 12:22:13 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_num(long long num, int plus_minus, int next_number)
{
	if (num >= 922337203685477581)
		return (0);
	num *= 10;
	if (plus_minus > 0)
	{
		if (num > 9223372036854775807 - next_number)
			return (0);
	}
	else
	{
		if (num - 1 > 9223372036854775807 - next_number)
			return (0);
	}
	return (1);
}

int	check_exit_code(char *arg, long long *num)
{
	int	plus_minus;

	while (9 <= *arg && *arg <= 13)
		arg++;
	if (*arg == '+' || *arg == '-')
	{
		plus_minus = 1;
		if (*(arg++) == '-')
			plus_minus = -1;
	}
	while ('0' <= *arg && *arg <= '9' && \
		check_num(*num, plus_minus, *arg - '0'))
		*num = *num * 10 + (*(arg++) - '0');
	while (9 <= *arg && *arg <= 13)
		arg++;
	if (*arg)
		return (0);
	return (1);
}

void	ft_exit(char *arg, int size)
{
	long long	num;

	num = 0;
	if (!arg)
	{
		printf("exit\n");
		exit(0);
	}
	if (!check_exit_code(arg, &num))
	{
		if (size == 1)
			printf("exit\n");
		error_excute("exit", arg, "numeric argument required", 255);
	}
	printf("exit\n");
	exit((unsigned char)num);
}

int	ft_cd(char *path)
{
	char	*new_path;
	int		ret;

	ret = 0;
	if (!path)
		ret = chdir(getenv("HOME"));
	else if (*path == '~')
	{
		if (!path[1])
			ret = chdir(getenv("HOME"));
		else
		{
			new_path = ft_strjoin(getenv("HOME"), path + 1);
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
