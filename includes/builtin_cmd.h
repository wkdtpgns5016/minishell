#ifndef BUILTIN_CMD_H
# define BUILTIN_CMD_H

int		ft_echo(int opt, char *str);
int		ft_pwd(void);
int		ft_env(t_list *l);
int		ft_export(char *arg, t_ev *ev);
int		ft_unset(char *arg, t_ev *ev);
void	ft_exit(char *arg, int size);
int		ft_cd(char *path, t_list *evl);
void	swap_s(char **s, int p, int c);
void	sort_s(char **s, int len);
void	write_s(char **s);
void	write_l(t_list *l);
void	ft_error(char *cmd, char *arg, char *msg);
int		check_num(long long num, int mark, char plus);
int		switch_envl(t_list *new, t_list *now, t_list *last, t_list **l);
int		delete_envl(char *arg, t_list *now, t_list *last, t_list **l);
char	**l_to_p(t_list *evl);

#endif
