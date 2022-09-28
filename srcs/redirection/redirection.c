/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:24 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/28 08:47:47 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/history.h>

extern int	g_signal_flag;

void	in_redir(int dst, char *infile, int heredoc_flag)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	dup2(infile_fd, dst);
	close(infile_fd);
	if (heredoc_flag)
		unlink(infile);
}

void	write_heredoc(int fd, char *limiter, t_info *info)
{
	char		*buffer;
	t_cursor	cursor;

	while (1)
	{
		get_cursor_position(&cursor.col, &cursor.row);
		buffer = readline("> ");
		if (g_signal_flag == 2)
			break ;
		if (buffer == 0)
		{
			move_cursor(cursor.col + 2, cursor.row);
			break ;
		}
		if (write_heredoc_file(fd, &buffer, limiter, info) == 0)
			break ;
		ft_free((void **)&buffer);
	}
	if (buffer != 0)
		ft_free((void **)&buffer);
}

char	*get_heredoc(char *limiter, t_info *info)
{
	int		fd;
	int		backup;
	char	*filename;

	g_signal_flag = 1;
	backup = dup(0);
	filename = make_temp_file();
	if (filename == 0)
		return (0);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	write_heredoc(fd, limiter, info);
	dup2(backup, 0);
	close(backup);
	close(fd);
	return (filename);
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
	close(outfile_fd);
}

void	redirection(t_cmds *cmds, t_info *info)
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
			process_redir(temp, flag, i, cmds->heredoc_flag, info);
			cmds->cmd = remove_redir(temp, i, i + 1);
			ft_free_arr(&temp);
		}
		else
			i++;
	}
}
