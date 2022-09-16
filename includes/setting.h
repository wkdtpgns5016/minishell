/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:59:22 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:59:23 by sehjang          ###   ########.fr       */
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

void	main_handler(int sig);
void	sub1_handler(int sig);
void	set_terminal(void);
void	ret_terminal(void);
void	get_ev(t_ev *ev, char **envp);

#endif
