#include "../includes/minishell.h"

char	*add_str_between_pipe(char *str, char *add)
{
	char	*temp;
	char	*new;

	new = ft_strjoin(str, " | ");
	if (new == 0)
		return (0);
	temp = new;
	new = ft_strjoin(temp, add);
	if (new == 0)
		return (0);
	ft_free((void **)&temp);
	return (new);
}

char	*make_cmd_pipe(char *content)
{
	char	**split;
	char	*new;
	char	*temp;
	int		i;

	split = ft_split(content, '|');
	if (split == 0)
		return (0);
	if (*split == 0)
	{
		ft_free_arr((char ***)&split);
		return (ft_strdup(content));
	}
	i = 1;
	new = ft_strdup(split[0]);
	if (new == 0)
	{
		ft_free_arr((char ***)&split);
		return (0);
	}
	while (split[i] != 0)
	{
		temp = new;
		new = add_str_between_pipe(temp, split[i]);
		ft_free((void **)&temp);
		if (new == 0)
		{
			ft_free_arr((char ***)&split);
			return (0);
		}
		i++;
	}
	ft_free_arr((char ***)&split);
	return (new);
}
