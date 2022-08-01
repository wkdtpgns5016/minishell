#include "../includes/minishell.h"

void	in_redir(int dst, char *infile)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	dup2(infile_fd, dst);
}

void	get_heredoc(char *limiter)
{
	char	buffer[1024];
	int		fd;
	int		size;
	char	*check;

	check = ft_strjoin(limiter, "\n");
	if (check == 0)
		return ;
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (1)
	{
		ft_putstr_fd(">", 1);
		size = read(0, buffer, 1024);
		if (size < 0)
			return ;
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
	int	mode;

	if (flag)
		mode = O_WRONLY | O_CREAT | O_APPEND;
	else
		mode = O_WRONLY | O_CREAT | O_TRUNC;
	outfile_fd = open(outfile, mode, 0644);
	dup2(outfile_fd, src);
}

void	redirection(t_cmds *cmds)
{
	char	**temp;
	int		i;
	int		flag;

	i = 0;
	while ((cmds->cmd)[i] != 0)
	{
		flag = is_redir((cmds->cmd)[i]);
		if (flag)
		{
			temp = cmds->cmd;
			if (i == 0)
			{
				process_redir(temp, flag, i, 1);
				cmds->cmd = remove_redir(temp, i, i + 1);
			}
			else
			{
				if (is_num_str(temp[i - 1]))
				{
					process_redir(temp, flag, i, 0);
					cmds->cmd = remove_redir(temp, i - 1, i + 1);
				}
				else
				{
					process_redir(temp, flag, i, 1);
					cmds->cmd = remove_redir(temp, i, i + 1);
				}
			}
			ft_free_arr(&temp);
		}
		else
			i++;
	}
}
