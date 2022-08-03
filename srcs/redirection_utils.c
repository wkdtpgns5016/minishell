#include "../includes/minishell.h"

int	is_redir(char *c)
{
	if (*c == '<' && *(c + 1) != '<')
		return (INPUT_REDIR);
	else if (*c == '<' && *(c + 1) == '<')
		return (HERE_DOC_REDIR);
	else if (*c == '>' && *(c + 1) != '>')
		return (OUTPUT_TRUNC_REDIR);
	else if (*c == '>' && *(c + 1) == '>')
		return (OUTPUT_APPAND_REDIR);
	return (0);
}

int	get_index_arr(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != 0)
		i++;
	return (i);
}

char	**remove_redir(char **cmd, int start, int end)
{
	char	**new;
	int		len;
	int		remove_num;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = get_index_arr(cmd);
	remove_num = end - start + 1;
	new = (char **)malloc(sizeof(char *) * (len - remove_num + 1));
	while (j < len - remove_num)
	{
		if (i >= start && i <= end)
			i++;
		else
			new[j++] = ft_strdup(cmd[i++]);
	}
	new[j] = 0;
	return (new);
}
