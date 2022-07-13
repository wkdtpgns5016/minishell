/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:56:40 by sehjang           #+#    #+#             */
/*   Updated: 2022/03/15 14:07:03 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*new;
	t_list	*list;

	temp = lst;
	list = 0;
	while (temp != 0)
	{
		new = ft_lstnew(f(temp->content));
		if (new == 0)
		{
			ft_lstclear(&list, del);
			return (list);
		}
		ft_lstadd_back(&list, new);
		temp = temp->next;
	}
	return (list);
}
