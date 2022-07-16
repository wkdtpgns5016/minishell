#ifndef SIGNAL_H
# define SIGNAL_H

# define CTRL_C 2
# define CTRL_SLASH 3

void	handler(int sig);
void	set_terminal(void);
void	ret_terminal(void);

#endif
