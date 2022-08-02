#include "../includes/minishell.h"
/*
void	ft_unset(char *arg, t_list **evl)
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
*/

void	ft_export(char *arg, t_ev *ev)
{
	char	*content;
	t_list	*last;
	t_list	*now;
	t_list	*new;

	if (!arg)
	{
		write_s(ev->evp);
		return ;
	}
	content = ft_strdup(arg);
	if (!content)
		exit(1);
	new = ft_lstnew(content);
	if (!new)
		exit(1);
	now = ev->evl;
	last = NULL;
	while (now)
	{
		if (switch_envl(new, now, last, &ev->evl))
			break ;
		last = now;
		now = now->next;
	}
	if (!now)
		ft_lstadd_back(&ev->evl, new);
	ev->evp = l_to_p(ev->evl);
}
