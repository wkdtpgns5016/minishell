#include "../../includes/minishell.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	get_line_idx(char *line)
{
	int		idx;
	char	quote;

	idx = 0;
	quote = 0;
	while (*line && !(ft_isspace(*line) && !quote))
	{
		if (!quote)
		{
			if (*line == '"')
				quote = '"';
			else if (*line == '\'')
				quote = '\'';
		}
		else
		{
			if (*line == quote)
				quote = 0;
		}
		line++;
		idx++;
	}
	return (idx);
}

t_list	*line2list(char *line)
{
	char	*line_cpy;
	char	*line_1d;
	t_list	*line_lst;
	int		idx;

	line_cpy = line;
	line_1d = NULL;
	line_lst = NULL;
	idx = 0;
	while (*line)
	{
		idx = get_line_idx(line);
		line_1d = ft_substr(line, 0, idx);
		ft_lstadd_back(&line_lst, ft_lstnew(line_1d));
		line += idx;
		while (*line && ft_isspace(*line))
			line++;
	}
	free(line_cpy);
	return (line_lst);
}

char	**list2line(t_list *line_lst)
{
	char	**line_2d;
	t_list	*line_lst_cpy;
	int		idx;

	line_2d = (char **)malloc(sizeof(char *) * (ft_lstsize(line_lst) + 1));
	if (!line_2d)
		exit(1);
	idx = 0;
	while (line_lst)
	{
		line_2d[idx++] = line_lst->content;
		line_lst_cpy = line_lst;
		line_lst = line_lst->next;
		free(line_lst_cpy);
	}
	line_2d[idx] = 0;
	return (line_2d);
}

char	**divide_line(char *line)
{
	return (list2line(line2list(line)));
}
