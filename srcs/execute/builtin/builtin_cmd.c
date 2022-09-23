/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:55:04 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 17:43:08 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	excute_echo(char **cmd)
{
	int	status;

	if (cmd[1] != 0)
	{
		if (!ft_memcmp(cmd[1], "-n", 3))
			status = ft_echo(1, cmd[2]);
		else
			status = ft_echo(0, cmd[1]);
	}
	else
		status = ft_echo(0, cmd[1]);
	return (status);
}

int	ft_echo(int opt, char *arg)
{
	if (arg)
		write(1, arg, ft_strlen(arg));
	if (!opt)
		write(1, "\n", 1);
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
