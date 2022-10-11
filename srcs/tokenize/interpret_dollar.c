#include "../../includes/minishell.h"
#include <stdlib.h>

t_list	*separate_dollar(t_list *now)
{
	char	c;
	t_list	*prev;
	t_list	*next;

	prev = now;
	now = now->next;
	while (now)
	{
		c = *(char *)now->content;
		if (c == '?')
		{
			prev = now;
			now = now->next;
			break ;
		}
		else if (!(ft_isalnum(c) || c == '_'))
			break ;
		prev = now;
		now = now->next;
	}	
	prev->next = NULL;
	next = now;
	return (next);
}

char	*make_dollar_str(t_list *dollar_lst)
{
	char	*dollar_str;
	int		idx;
	t_list	*temp;

	dollar_str = (char *)malloc(sizeof(char) * (ft_lstsize(dollar_lst) + 1));
	if (!dollar_str)
		exit(1);
	idx = -1;
	while (dollar_lst)
	{
		dollar_str[++idx] = *(char *)dollar_lst->content;
		temp = dollar_lst;
			dollar_lst = dollar_lst->next;
		ft_lstdelone(temp, free);
	}
	dollar_str[idx] = 0;
	return (dollar_str);
}

t_list	*new_dollar2env(t_list *dollar, t_info *info)
{
	t_list	*next;
	t_list	*last;

	next = separate_dollar(dollar);
	//dollar_str = make_dollar_str(dollar);
	change_node(&dollar, info);
	last = ft_lstlast(dollar);
	last->next = next;
	return (dollar);
}

void	interpret_dollar(t_list *quote_lst, t_info *info)
{
	t_list	*prev;
	char	c;

	prev = NULL;
	c = 0;
	while (quote_lst)
	{
		c = *(char *)(quote_lst)->content;
		while (c == '$')
		{
			prev->next = new_dollar2env(quote_lst, info);
			(quote_lst) = prev->next;
			c = *(char *)(quote_lst)->content;
		}
		prev = quote_lst;
		(quote_lst) = (quote_lst)->next;
	}
}
