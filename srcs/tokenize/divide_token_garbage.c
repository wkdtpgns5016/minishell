#include "../../includes/minishell.h"

int	is_token_garbage(char *str)
{
	if (ft_strchr(str, '\"') == 0 && ft_strchr(str, '\'') == 0)
	{
		if (ft_strchr(str, '<') != 0 || ft_strchr(str, '>') != 0 || \
		ft_strchr(str, '|') != 0)
			return (1);
	}
	return (0);
}

int	count_token_garbage(char **token)
{
	int		i;
	int		count;
	int		size;
	char	**temp_arr;
	char	*temp;

	i = 0;
	count = 0;
	while (token[i] != 0)
	{
		size = 0;
		if (is_token_garbage(token[i]))
		{
			temp = make_cmd_pipe_amd_redir(token[i]);
			temp_arr = ft_split(temp, ' ');
			ft_free((void **)&temp);
			while (temp_arr[size] != 0)
				size++;
			ft_free_arr((char ***)&temp_arr);
			count += size;
		}
		else
			count++;
		i++;
	}
	return (count);
}

int	insert_divide_token(char ***arr, char *token, int *index)
{
	char	**divide_redir;
	int		size;
	int		i;

	size = 0;
	i = 0;
	divide_redir = create_divide_token(token);
	while (divide_redir[size] != 0)
		size++;
	while (i < size)
	{
		(*arr)[*index + i] = ft_strdup(divide_redir[i]);
		i++;
	}
	(*index) += size;
	ft_free_arr(((char ***)&divide_redir));
	return (size);
}

char	**divide_token_garbage(char **token)
{
	int		i;
	int		j;
	int		size;
	char	**new;

	i = 0;
	j = 0;
	size = count_token_garbage(token);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		if (is_token_garbage(token[j]))
			insert_divide_token(&new, token[j], &i);
		else
			new[i++] = ft_strdup(token[j]);
		j++;
	}
	new[i] = 0;
	return (new);
}
