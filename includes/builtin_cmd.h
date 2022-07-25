#ifndef BUILT_IN_CMD_H
# define BUILT_IN_CMD_H

void	ft_echo(int opt, char *str);
void	ft_pwd(void);
void	ft_env(t_list *envl);
void	ft_export(char *arg, t_list **envl);
void	ft_unset(char *arg, t_list **envl);
void	ft_exit(char *arg);
void	ft_cd(char *path);
void	swap_s(char **s, int p, int c);
void	sort_s(char **s, int len);
void	write_s(char **s);
void	write_envl(t_list *envl);
void	ft_error(char *cmd, char *arg, char *msg);
t_list *get_envl(char **envp);
int	check_num(long long num, int mark, char plus);
int	switch_envl(t_list *new, t_list *now, t_list *last, t_list **envl);
int	delete_envl(char *arg, t_list *now, t_list *last, t_list **envl);
#endif
