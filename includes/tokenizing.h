#ifndef TOKENIZING_H
# define TOKENIZING_H

# include "./struct.h"

char 	**divide_line(char *line);
t_cmds	*insert_cmds(char **token, t_info *info);
char	**divide_redir_garbage(char **token);
char	**create_divide_redir(char *redir);
t_cmds	*new_set_cmds(t_info *info, char *line);
void	interpret_cmds(t_cmds *cmds, t_info *info);
void	interpret_dollar(t_list **quote_lst, t_info *info);

#endif
