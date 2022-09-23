/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:21 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:57:22 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**find_path(char **envp, char *key)
{
	char	**arr;
	char	*path;
	int		i;

	i = 0;
	path = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], key, ft_strlen(envp[i])))
		{
			path = ft_substr(envp[i], ft_strlen(key), ft_strlen(envp[i]));
			if (path == 0)
				return (0);
			break ;
		}
		i++;
	}
	if (path == 0)
		return (0);
	arr = ft_split(path, ':');
	if (arr == 0)
		return (0);
	ft_free((void **)&path);
	return (arr);
}

char	*find_cmd(char **cmd_arg, char **envp)
{
	int		i;
	char	*cmd;
	char	*temp;
	char	**path;

	i = 0;
	path = find_path(envp, "PATH=");
	if (path == 0)
		return (0);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (temp == 0)
			return (0);
		cmd = ft_strjoin(temp, cmd_arg[0]);
		ft_free((void **)&temp);
		if (cmd == 0)
			return (0);
		if (access(cmd, X_OK) == 0)
			break ;
		ft_free((void **)&cmd);
		i++;
	}
	ft_free_arr(&path);
	return (cmd);
}

void	execute_cmd(char **cmd, char **envp)
{
	char	*cmd_path;

	if (access(*cmd, X_OK) == 0)
		cmd_path = ft_strdup(*cmd);
	else
		cmd_path = find_cmd(cmd, envp);
	if (cmd_path == 0)
	{
		error_excute(*cmd, 0, "command not found", 127);
	}
	if (execve(cmd_path, cmd, envp) == -1)
	{
		error_excute(*cmd, 0, strerror(errno), errno);
	}
}
