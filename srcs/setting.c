#include "../includes/minishell.h"

void	handler(int sig)
{
	if (sig == CTRL_C)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == CTRL_SLASH)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_terminal()
{
	struct termios new_term;

	tcgetattr(0, &new_term);
	new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new_term);

}

void	ret_terminal()
{
	struct termios new_term;

	tcgetattr(0, &new_term);
	new_term.c_lflag &= ECHOCTL;
	tcsetattr(0, TCSANOW, &new_term);

}

void	get_ev(t_ev *ev, char **envp)
{
	int	idx;
	t_list	*new;
	char	*content;
	char	**p;

	idx = 0;
	while (envp[idx])
		idx++;
	p = (char **)malloc(sizeof(char *) * (idx + 2));
	if (!p)
		exit(1);
	p[0] = NULL;
	p[idx + 1] = NULL;
	ev->evl = NULL;
	idx = -1;
	while (envp[++idx])
	{
		content = ft_strdup(envp[idx]);
		new = ft_lstnew(content);
		ft_lstadd_back(&(ev->evl), new);
		p[idx + 1] = content;
	}
	sort_s(p, idx - 1);
	ev->evp = p;
}
