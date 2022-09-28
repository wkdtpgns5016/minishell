#include "../../includes/minishell.h"
#include <stdio.h>

char	*list2dollar(t_list **first_node)
{
	char	*dollar;
	int		idx;

	dollar = (char *)malloc(sizeof(ft_lstsize(*first_node)));
	if (!dollar)
		exit (1);
	idx = 0;
	change_first_node(first_node);
	while (*first_node)
	{
		dollar[idx] = *(char *)((*first_node)->content);
		change_first_node(first_node);
		idx++;
	}
	dollar[idx] = '\0';
	return (dollar);
}

char	*dollar2env(t_list *evl)
{
	char *evp;

	if (!evl)
		return (ft_strdup(""));
	evp = (char *)evl->content;
	while (*evp && *evp != '=')
		evp++;
	if (*evp)
		return (ft_strdup(++evp));
	else
		return (ft_strdup(""));
}

t_list	*env2node(char *dollar)
{
	t_list	*first_node;

	first_node = NULL;
	while (*dollar)
		dollar = we_meet_char(dollar, &first_node);	
	return (first_node);
}

void change_node(t_list **first_node, t_info *info)
{
	char	*dollar;
	t_list	*evl;

	evl = info->ev.evl;
	dollar = list2dollar(first_node);
	while (evl)
	{
		if (check_envl(evl->content, dollar))
			break;
		evl = evl->next;
	}
	free(dollar);
	dollar = dollar2env(evl);
	*first_node = env2node(dollar);
	free(dollar);
	dollar = NULL;
}
