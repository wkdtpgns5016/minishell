#include "../includes/minishell.h"

void	ft_unset(char *arg, t_list **envl)
{
	t_list	*last;
	t_list	*now;

	if (!arg)
		return ;
	if (ft_strchr(arg, '='))
	{
		ft_error("unset", arg, "not a valid identifier");
		return ;
	}
	last = NULL;
	now = *envl;	
	while (now)
	{
		if (delete_envl(arg, now, last, envl))
			return ;
		last = now;
		now = now->next;
	}
}

void	ft_export(char *arg, t_list **envl)
{
	char	*content;
	t_list	*last;
	t_list	*now;
	t_list	*new;

	if (!arg)
	{
		write_envl(*envl);
		return ;
	}
	content = ft_strdup(arg);
	if (!content)
		exit(1);
	new = ft_lstnew(content);
	if (!new)
		exit(1);
	now = *envl;
	last = NULL;
	while (now)
	{
		if (switch_envl(new, now, last, envl))
			return ;
		last = now;
		now = now->next;
	}
	ft_lstadd_back(envl, new);
}
