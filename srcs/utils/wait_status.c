/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:52 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:58:53 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_exit_status(int status)
{
	return (((status) & 0xff00) >> 8);
}

int	is_exit_by_signal(int status)
{
	return (((signed char)(((status) & 0x7f) + 1) >> 1) > 0);
}

int	get_exit_signal_number(int status)
{
	return ((status) & 0x7f);
}
