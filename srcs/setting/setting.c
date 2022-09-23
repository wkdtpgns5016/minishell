/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:47 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/23 09:47:46 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	set_terminal(void)
{
	struct termios	new_term;

	tcgetattr(0, &new_term);
	new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_term);
}

void	ret_terminal(void)
{
	struct termios	new_term;

	tcgetattr(0, &new_term);
	new_term.c_lflag &= ECHOCTL;
	tcsetattr(0, TCSANOW, &new_term);
}

void	get_ev(t_ev *ev, char **envp)
{
	int		idx;
	t_list	*new;
	char	*content;
	char	**p;

	idx = 0;
	while (envp[idx])
		idx++;
	p = (char **)malloc(sizeof(char *) * (idx + 2));
	if (!p)
		exit(1);
	p[0] = NULL;
	p[idx + 1] = NULL;
	ev->evl = NULL;
	idx = -1;
	while (envp[++idx])
	{
		content = ft_strdup(envp[idx]);
		new = ft_lstnew(content);
		ft_lstadd_back(&(ev->evl), new);
		p[idx + 1] = content;
	}
	sort_s(p, idx - 1);
	ev->evp = p;
}

int	setting(t_info *info, char **envp)
{
	set_terminal();
	get_ev(&info->ev, envp);
	return (1);
}