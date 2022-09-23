/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:29:52 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 12:29:53 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*make_exit_code(int	**arr, int size)
{
	int	*temp;

	temp = *arr;
	temp = (int *)malloc(sizeof(int) * (size + 1));
	temp[size] = -1;
	return (temp);
}

int	quit_exit_cmd(t_info *info, int signal_flag)
{
	t_cmds	*cmds;

	if (signal_flag == 2)
	{
		info->recent_exit_code = make_exit_code(&(info->recent_exit_code), 1);
		info->recent_exit_code[0] = 1;
		return (1);
	}
	cmds = info->cmds;
	if (cmds == 0)
		return (1);
	return (0);
}
