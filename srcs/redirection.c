/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:24 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 11:31:52 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>

extern int	g_signal_flag;

void	in_redir(int dst, char *infile)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	dup2(infile_fd, dst);
}

void	get_heredoc(char *limiter)
{
	char	*buffer;
	int		fd;
	int		size;
	int		backup;

	g_signal_flag = 1;
	backup = dup(0);
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (1)
	{
		buffer = readline("> ");
		if (buffer == 0)
			break ;
		if (ft_strlen(buffer) > ft_strlen(limiter))
			size = ft_strlen(buffer);
		else
			size = ft_strlen(limiter);
		if (ft_strncmp(buffer, limiter, size) == 0)
		{
			ft_free((void **)&buffer);
			break ;
		}
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		ft_free((void **)&buffer);
	}
	dup2(backup, 0);
	close(backup);
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
				process_redir(temp, flag, i);
				cmds->cmd = remove_redir(temp, i, i + 1);
			}
			else
			{
				if (is_num_str(temp[i - 1]))
				{
					process_redir_with_num(temp, flag, i);
					cmds->cmd = remove_redir(temp, i - 1, i + 1);
				}
				else
				{
					process_redir(temp, flag, i);
					cmds->cmd = remove_redir(temp, i, i + 1);
				}
			}
			ft_free_arr(&temp);
		}
		else
			i++;
	}
}
