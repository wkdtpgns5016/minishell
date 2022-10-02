/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:59:22 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 13:21:47 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTING_H
# define SETTING_H

# define CTRL_C 2
# define CTRL_SLASH 3

typedef struct s_ev
{
	char	**evp;
	t_list	*evl;
}	t_ev;

struct termios	set_terminal_for_cursor(void);
void	set_terminal_in_cmd(void);
void	set_terminal_in_wait(void);
void	set_signal_in_wait(void);
void	set_signal_in_cmd(void);
void	setting_in_cmd(void);
void	setting_in_wait(void);
void	get_ev(t_ev *ev, char **envp);

#endif
