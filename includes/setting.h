/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:59:22 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/04 20:40:19 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTING_H
# define SETTING_H

# define CTRL_C 2
# define CTRL_SLASH 3

struct termios	set_terminal_for_cursor(void);
void			echo_ctrl_char(void);
void			dont_echo_ctrl_char(void);
void			cmd_handler(int sig);
void			heredoc_handler(int sig);
void			main_handler(int sig);
void			cmd_setting(void);
void			heredoc_setting(void);
void			main_setting(void);
int				is_end_of_window(int row);
void			move_cursor_main(int col, int row);

#endif
