#include "../includes/minishell.h"

void	ft_unset(char *arg, t_ev *ev)
{
	t_list	*last;
	t_list	*now;

	if (!arg)
		return ;
	if (ft_strchr(arg, '='))
	{
		error_excute("unset", arg, "not a valid identifier", 255);
		return ;
	}
	last = NULL;
	now = ev->evl;
	while (now)
	{
		if (delete_envl(arg, now, last, &ev->evl))
			break ;
		last = now;
		now = now->next;
	}
	if (now)
		ev->evp = l_to_p(ev->evl);
}


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
	new = ft_lstnew(content);
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
