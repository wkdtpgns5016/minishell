#ifndef TOKENIZE_H
# define TOKENIZE_H

t_cmds	*insert_cmds(char **token, t_info *info);
char	**divide_redir_garbage(char **token);
char	**create_divide_redir(char *redir);

#endif