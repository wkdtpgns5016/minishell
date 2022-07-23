#include "../includes/minishell.h"

int	check_num(long long  num, int mark, char plus)
{
	if (num >= 922337203685477581)
		return (0);
	num *= 10;
	if (mark > 0)
	{
		if (num > 9223372036854775807 - plus)
			return (0);
	}
	else
	{
		if (num - 1 > 9223372036854775807 - plus)
			return (0);
	}
	return (1);
}

int	switch_envl(t_list *new, t_list *now, t_list *last, t_list **envl)
{
	char	*s;
	char	*arg;

	s = (char *)now->content;
	arg = (char *)new->content;
	if (ft_strlen(arg) != ft_strlen(s) - ft_strlen(ft_strchr(s, '=')) && \
		ft_strlen(arg) != ft_strlen(s))
		return (0);
	if (ft_memcmp(s, arg, ft_strlen(arg)))
		return (0);
	if (!last)
		*envl = new;
	else
		last->next = new;
	new->next = now->next;
	free(now->content);
	free(now);
	return (1);
}

void	write_envl(t_list *envl)
{
	int	len;
	char	**s;
	int	idx;

	len = ft_lstsize(envl);
	s = (char **)malloc(sizeof(char *) * (len + 2));
	s[0] = NULL;
	s[len + 1] = NULL;
	idx = 0;
	while (envl)
	{
		s[++idx] = envl->content;
		envl = envl->next;
	}
	sort_s(s, len - 1);
	write_s(s);
	free(s);
}

int	delete_envl(char *arg, t_list *now, t_list *last, t_list **envl)
{
	char	*s;

	now = last->next;
	s = (char *)now->content;
	if (ft_strlen(arg) != ft_strlen(s) - ft_strlen(ft_strchr(s, '=')))
		return (0);
	if (ft_memcmp(s, arg, ft_strlen(arg)))
		return (0);
	if (!last)
		*envl = now->next;
	else
		last->next = now->next;
	free(now->content);
	free(now);
	return (1);
}
