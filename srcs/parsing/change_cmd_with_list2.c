#include "../../includes/minishell.h"

void	change_first_node(t_list **first_node)
{
	t_list	*temp;

	temp = *first_node;
	*first_node = (*first_node)->next;
	free(temp->content);
	temp->content = NULL;
	free(temp);
	temp = NULL;
}

char	*list2char(t_list **first_node)
{
	char	*dollar;
	int		idx;

	dollar = (char *)malloc(sizeof(char) * ft_lstsize(*first_node) + 1);
	if (!dollar)
		exit (1);
	idx = 0;
	while (*first_node)
	{
		dollar[idx] = *(char *)((*first_node)->content);
		change_first_node(first_node);
		idx++;
	}
	dollar[idx] = '\0';
	return (dollar);
}

void	change_line(char **line, t_info *info)
{
	t_list	*line_char_list;

	line_char_list = char2list(*line, info);
	free(*line);
	*line = list2char(&line_char_list);
}
