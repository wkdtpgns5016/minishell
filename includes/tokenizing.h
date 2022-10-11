/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:04:56 by sehjang           #+#    #+#             */
/*   Updated: 2022/10/11 16:04:57 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZING_H
# define TOKENIZING_H

# include "./struct.h"

char	**divide_line(char *line);
t_cmds	*insert_cmds(char **token, t_info *info);
char	**divide_token_garbage(char **token);
char	**create_divide_token(char *redir);
t_cmds	*new_set_cmds(t_info *info, char *line);
void	interpret_cmds(t_cmds *cmds, t_info *info);
void	interpret_dollar(t_list *quote_lst, t_info *info);
void	no_quote_interpret_dollar(t_list **cmd_lst, t_info *info, char **cmd);
void	ft_lstadd_back_with_dup(t_list **lst, char c);
t_list	*add_char_list(char *cmd, t_info *info);

#endif
