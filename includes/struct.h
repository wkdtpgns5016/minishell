#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_cmds
{
	char			**cmd;
	int				fd[2];
	pid_t			pid;
	struct s_cmds	*next;
	struct s_cmds	*pred;
	char			*heredoc_filepath;
	int				heredoc_flag;
}	t_cmds;

typedef struct s_ev
{
	char	**evp;
	t_list	*evl;
}	t_ev;

typedef struct s_info
{
	t_cmds	*cmds;
	t_ev	ev;
	int		backup[2];
	int		*recent_exit_code;
	char	**envp;
	char	*history_cmd;
}	t_info;

typedef struct s_cursor
{
	int	col;
	int	row;
}	t_cursor;

typedef struct s_builtin_info
{
	int		flag;
	int		backup[2];
}	t_builtin_info;

#endif
