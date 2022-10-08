#include "../../includes/minishell.h"

int	get_size_divide_redir(char *redir)
{
	int	size;
	int	i;
	int	redir_mode;

	size = 1;
	i = 0;
	while (redir[i] != 0)
	{
		redir_mode = 0;
		if (redir[i] == '<' || redir[i] == '>')
		{
			redir_mode = is_redir(redir + i);
			if (redir_mode == INPUT_REDIR || redir_mode == OUTPUT_TRUNC_REDIR)
				i += 1;
			else if (redir_mode == HERE_STRING_REDIR)
				i += 3;
			else
				i += 2;
			size++;
		}
		else
			i++;
	}
	return (size);
}

char	**create_divide_redir(char *redir)
{
	char	**divide_redir;
	char	*temp;
	int		size;

	size = get_size_divide_redir(redir);
	temp = make_cmd_redir(redir);
	divide_redir = ft_split(temp, ' ');
	ft_free((void **)&temp);
	return (divide_redir);
}
