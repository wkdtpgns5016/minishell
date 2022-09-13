#include "../includes/minishell.h"

int	ft_unset(char *arg, t_ev *ev)
{
	t_list	*last;
	t_list	*now;

	if (!arg)
		return (1);
	if (ft_strchr(arg, '='))
	{
		print_error_message_with_token("unset", arg, "not a valid identifier");
		return (255);
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
	return (0);
}

int	ft_export(char *arg, t_ev *ev)
{
	char	*content;
	t_list	*last;
	t_list	*now;
	t_list	*new;

	if (!arg)
	{
		write_s(ev->evp);
		return (0);
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
	return (0);
}
