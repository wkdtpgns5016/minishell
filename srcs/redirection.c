/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:24 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 15:42:13 by sunwchoi         ###   ########.fr       */
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

void	write_heredoc(int fd, char *limiter)
{
	char	*buffer;
	int		size;
	int		backup;
	t_cursor cursor;

	while (1)
	{
		get_cursor_position(&cursor.col, &cursor.row);
		buffer = readline("> ");
		if (buffer == 0)
		{
			move_cursor(cursor.col + 2, cursor.row - 1);
			break ;
		}
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
}

void	get_heredoc(char *limiter)
{
	int		fd;
	int		backup;

	g_signal_flag = 1;
	backup = dup(0);
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	write_heredoc(fd, limiter);
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
			process_redir(temp, flag, i);
			cmds->cmd = remove_redir(temp, i, i + 1);
			ft_free_arr(&temp);
		}
		else
			i++;
	}
}
