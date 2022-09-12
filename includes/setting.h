#ifndef SETTING_H
# define SETTING_H

# define CTRL_C 2
# define CTRL_SLASH 3

typedef struct s_ev
{
	char **evp;
	t_list *evl;

}	t_ev;

void	main_handler(int sig);
void	sub1_handler(int sig);
void	sub2_handler(int sig);
void	set_terminal(void);
void	ret_terminal(void);
void	get_ev(t_ev *ev, char **envp);

#endif
