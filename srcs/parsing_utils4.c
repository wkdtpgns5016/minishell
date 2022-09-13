#include "../includes/minishell.h"

char *change_dollar(char *dollar, t_list *evl)
{
	int	idx;

	idx = 0;
	while (dollar[idx])
	{
		if (!(ft_isalnum((int)dollar[idx]) || *dollar == '_'))
		{
			*dollar = 0;
			break ;
		}
		idx++;
	}
	while (evl)
	{
		if (check_envl(evl->content, dollar))
			return (evl->content);
		evl = evl->next;
	}
	return (" ");
}

char	*make_new_cmd(char *cmd, char *env, int org_size)
{
	int		env_size;
	int		total;
	char	*new_cmd;
	int		idx;

	env_size = 0;
	env = ft_strchr(env, '=');
	if (env)
		env_size = ft_strlen(++env);
	total = ft_strlen(cmd) + env_size - org_size;
	new_cmd = (char *)malloc(sizeof(char) * (total + 1));
	if (!new_cmd)
		return (NULL);
	new_cmd[total] = 0;
	idx = 0;
	while (*cmd != '$')
		new_cmd[idx++] = *(cmd++);
	cmd += org_size + 1;
	if (env)
		while (*env)
			new_cmd[idx++] = *(env++);
	while (*cmd)
		new_cmd[idx++] = *(cmd++);
	return (new_cmd);
}

void	dollar2env(char **cmd, t_info *info)
{
	char	*dollar;
	char	*new_cmd;

	dollar = ft_strdup(ft_strchr(*cmd, '$') + 1);
	if (!dollar)
		exit(1);
	else if (*dollar == '?')
		new_cmd = ft_itoa(*info->recent_exit_code);
	else
		new_cmd = make_new_cmd(*cmd, change_dollar(dollar, \
			info->ev.evl), ft_strlen(dollar));
	if (!new_cmd)
		exit (1);
	free(*cmd);
	*cmd = new_cmd;
	free(dollar);
	dollar = NULL;
}

void	change_cmd(char **cmd, t_info *info)
{
	while (*cmd)
	{
		if (ft_strchr(*cmd, '$'))
			dollar2env(cmd, info);
		else
			cmd++;
	}
}
