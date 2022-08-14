#include "../includes/minishell.h"

void	terminate_dollar(char *dollar)
{
	if (dollar[0] == '?')
	{
		dollar[1] = 0;
		return ;
	}
	while (*dollar)
	{
		if (!(ft_isalnum((int)*dollar) || *dollar == '_'))
		{
			*dollar = 0;
			return ;
		}
		dollar++;
	}
	

}

char	*change_cmd(char *cmd, char *env, int org_size)//
{
	int	env_size;
	int	total;
	char	*new_cmd;
	int	idx;

	env_size = 0;
	env = ft_strchr(env, '=');
	if (env)
		env_size = ft_strlen(++env);
	total = ft_strlen(cmd) + env_size - org_size;
	new_cmd = (char *)malloc(sizeof(char) * (total + 1));
	if (!new_cmd)
		exit (1);
	new_cmd[total] = 0;
	idx = 0;
	while (*cmd != '$')
		new_cmd[idx++] = *(cmd++);
	cmd += org_size + 1;
	if (env)
	{
		while (*env)
			new_cmd[idx++] = *(env++);
	}
	while (*cmd)
		new_cmd[idx++] = *(cmd++);//
	return (new_cmd);
}

void	convert_env(char **cmd, t_list* evl)
{
	char *dollar;
	char *new_cmd;

	dollar = NULL;
	while (*cmd)
	{
		dollar = ft_strchr(*cmd, '$');
		if (dollar)
		{	
			dollar = ft_strdup(dollar + 1);
			if (!dollar)
				exit(1);
			terminate_dollar(dollar);
			while (evl)
			{
				if (check_envl(evl->content, dollar))
					break ;
				evl = evl->next;
			}
			if (!evl)
				new_cmd = change_cmd(*cmd, " ", ft_strlen(dollar));
			else
				new_cmd = change_cmd(*cmd, evl->content, ft_strlen(dollar));
			free(*cmd);
			*cmd = new_cmd;
			free(dollar);
			dollar = NULL;
		}
		else
			cmd++;
	}
}
