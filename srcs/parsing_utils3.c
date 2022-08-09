#include "../includes/minishell.h"

int	get_last_index_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
		i++;
	return (i - 1);
}

int	check_last_pipe(char *line)
{
	char	**arr;
	int		i;

	arr = ft_split(line, ' ');
	if (arr == 0)
		return (-1);
	i = get_last_index_arr(arr);
	if (ft_strncmp(arr[i], "|", ft_strlen(arr[i])) == 0)
	{
		ft_free_arr((char ***)&arr);
		return (1);
	}
	ft_free_arr((char ***)&arr);
	return (0);
}
