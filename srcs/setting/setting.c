/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:53:23 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/06 17:53:26 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_setting(void)
{
	echo_ctrl_char();
	signal(CTRL_C, cmd_handler);
	signal(CTRL_SLASH, cmd_handler);
}

void	main_setting(void)
{
	dont_echo_ctrl_char();
	signal(CTRL_C, main_handler);
	signal(CTRL_SLASH, SIG_IGN);
}

void	heredoc_setting(void)
{
	dont_echo_ctrl_char();
	signal(CTRL_C, heredoc_handler);
	signal(CTRL_SLASH, SIG_IGN);
}
