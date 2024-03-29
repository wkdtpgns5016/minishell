/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:55:52 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:55:53 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_envl(char *now, char *new)
{
	size_t	now_trash;
	size_t	new_trash;
	size_t	var_len;

	now_trash = 0;
	new_trash = 0;
	if (ft_strchr(now, '='))
		now_trash = ft_strlen(ft_strchr(now, '='));
	if (ft_strchr(new, '='))
		new_trash = ft_strlen(ft_strchr(new, '='));
	var_len = ft_strlen(new) - new_trash;
	if (ft_strlen(now) - now_trash != var_len)
		return (0);
	if (ft_memcmp(now, new, var_len))
		return (0);
	return (1);
}

int	switch_envl(t_list *new, t_list *now, t_list *last, t_list **envl)
{
	char	*s;
	char	*arg;

	s = (char *)now->content;
	arg = (char *)new->content;
	if (!check_envl(s, arg))
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

char	**l_to_p(t_list *evl)
{
	int		len;
	char	**s;
	int		idx;
	t_list	*now;

	len = ft_lstsize(evl);
	s = (char **)malloc(sizeof(char *) * (len + 2));
	s[0] = NULL;
	s[len + 1] = NULL;
	idx = 0;
	now = evl;
	while (now)
	{
		s[++idx] = now->content;
		now = now->next;
	}
	sort_s(s, len);
	return (s);
}

int	delete_envl(char *arg, t_list *now, t_list *last, t_list **envl)
{
	char	*s;

	s = (char *)now->content;
	if (!check_envl(s, arg))
		return (0);
	if (!last)
		*envl = now->next;
	else
		last->next = now->next;
	free(now->content);
	free(now);
	return (1);
}
