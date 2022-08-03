#include "../includes/minishell.h"

int	is_include_str(char *big, char *little, int len)
{
	int	i;
	int	j;
	int	idx;

	i = 0;
	idx = 0;
	while (big[idx] != 0 && i < len)
	{
		j = 0;
		while (*(big + idx + j) == *(little + j) && j < len)
		{
			j++;
			if (*(little + j) == 0)
				return (idx);
		}
		idx++;
		i++;
		if (len < i + (int)ft_strlen(little))
			break ;
	}
	return (-1);
}

int	check_pipe_after(char **token_arr, int index)
{
	int	check;

	check = 0;
	if (is_include_str(token_arr[index], "|", ft_strlen(token_arr[index])) == 0)
	{
		if (is_include_str(token_arr[index], "||", ft_strlen(token_arr[index])) == 0)
			check = print_error_message_syntax("||");
		else
			check = print_error_message_syntax("|");
	}
	return (check);
}

int	check_pipe(char **token_arr, int i)
{
	if (i == 0)
	{
		print_error_message_syntax("|");
		return (1);
	}
	else
	{
		if (check_pipe_after(token_arr, i + 1))
			return (1);
	}
	return (0);
}
