#include "../includes/minishell.h"

void	in_redir(int dst, char *infile)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	dup2(infile_fd, dst);
}

void	get_heredoc(char *limiter)
{
	char	buffer[100];
	int		fd;
	int		size;
	char	*check;

	check = ft_strjoin(limiter, "\n");
	if (check == 0)
		ft_error("Error", 1);
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_error("Error", 1);
	while (1)
	{
		ft_putstr_fd(">", 1);
		size = read(0, buffer, 100);
		if (size < 0)
			ft_error("Error", 1);
		buffer[size] = '\0';
		if (ft_strncmp(buffer, check, ft_strlen(buffer)) == 0)
			break ;
		write(fd, buffer, ft_strlen(buffer));
	}
	ft_free((void **)&check);
	close(fd);
}

void	out_redir(char *outfile, int flag)
{
	int	outfile_fd;
	int	flag;

	if (flag)
		flag = O_WRONLY | O_CREAT | O_APPEND;
	else
		flag = O_WRONLY | O_CREAT | O_TRUNC;
	outfile_fd = open(outfile, flag);
	dup2(outfile_fd, 1);
}

void	is_redir(t_cmds *cmds)
{
	char	**cmd;
	char	*before;
	char	*after;

	cmd = cmds->cmd;
	while (cmd != 0)
	{
		if (ft_strchr(*cmd, '<'))
		{
			if (ft_strlen(*cmd) == 1)
				in_redir(*(cmd + 1), 0);
			else
			{
				before = get_str_before_redir(cmd);
				after = get_str_after_redir(cmd);
				// case1 : [n]<infile case
				if (check_num_str(before))
				{
					if (after == 0)
						in_redir(*(cmd + 1), ft_atoi(before));
					else
						in_redir(after, ft_atoi(before));
					// cmd 재처리하기
				}
				// case2 : [!n]<infile case
				else
				{
					if (after == 0)
						in_redir(*(cmd + 1), 0);
					else
						in_redir(after, 0);
					// cmd 재처리하기
				}
				ft_free((void **)&before);
				ft_free((void **)&after);
			}
		}
		cmd++;
	}
}
