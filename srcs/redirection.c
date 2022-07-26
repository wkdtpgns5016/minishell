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

void	out_redir(int src, char *outfile, int flag)
{
	int	outfile_fd;
	int	flag;

	if (flag)
		flag = O_WRONLY | O_CREAT | O_APPEND;
	else
		flag = O_WRONLY | O_CREAT | O_TRUNC;
	outfile_fd = open(outfile, flag);
	dup2(outfile_fd, src);
}

void	redirection(t_cmds *cmds)
{
	char	**cmd;
	int		i;
	int		flag;

	cmd = cmds->cmd;
	i = 0;
	while (cmd[i] != 0)
	{
		flag = is_redir(cmd[i]);
		if (flag)
		{
			if (i == 0)
			{
				process_redir(cmds, flag, i, 1);
				//remove redir
			}
			else
			{
				if (is_num_str(cmd[i - 1]))
					process_redir(cmds, flag, i, 0);
				else
					process_redir(cmds, flag, i, 1);
				//remove redir
			}
		}
		i++;
	}
}
