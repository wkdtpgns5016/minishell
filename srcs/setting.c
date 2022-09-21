/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:47 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 13:47:27 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
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
	info->cursor_col = (int *)malloc(sizeof(int));
	info->cursor_row = (int *)malloc(sizeof(int));
	if (!info->cursor_col || !info->cursor_row)
		return (0);
	//get_cursor_position(info->cursor_col, info->cursor_row);
	return (1);
}
