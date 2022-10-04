/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:57:37 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/28 07:53:31 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_head_pipe(t_info *info, char *line)
{
	int		i;
	char	**word;

	i = 0;
	word = ft_split(line, ' ');
	if (word == 0)
		return (0);
	while (word[i] != 0)
		i++;
	if (i == 1 && ft_strncmp(*word, "|", ft_strlen(*word)) == 0)
	{
		print_error_message_syntax("|");
		info->recent_exit_code = make_exit_code(&(info->recent_exit_code), 1);
		info->recent_exit_code[0] = 258;
		ft_free_arr(&word);
		return (1);
	}
	ft_free_arr(&word);
	return (0);
}

t_cmds	*set_last_cmd(t_info *info, char *line)
{
	t_cmds	*cmd_list;
	char	*new;
	char	*temp;

	new = add_last_cmd(line, info);
	if (new == 0)
		return (0);
	ft_free((void **)&(info->history_cmd));
	info->history_cmd = ft_strdup(new);
	if (info->history_cmd == 0)
		exit(1);
	temp = new;
	new = make_cmd_pipe_amd_redir(temp);
	ft_free((void **)&temp);
	change_line(&new, info);
	cmd_list = make_cmds(new, info);
	ft_free((void **)&new);
	return (cmd_list);
}

t_cmds	*set_cmds(t_info *info, char *line)
{
	t_cmds	*cmd_list;
	int		flag;

	info->history_cmd = ft_strdup(line);
	if (info->history_cmd == 0)
		exit(1);
	if (check_head_pipe(info, line))
		return (0);
	flag = check_readline(line);
	if (flag != 0)
	{
		if (flag == 1)
		{
			info->recent_exit_code = \
			make_exit_code(&(info->recent_exit_code), 1);
			info->recent_exit_code[0] = 258;
		}
		return (0);
	}
	cmd_list = set_last_cmd(info, line);
	if (cmd_list == 0)
		return (0);
	return (cmd_list);
}

void	set_info(t_info *info, char *line)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	info->cmds = 0;
	if (*line != 0)
	{
		length = ft_strlen(line);
		while (i < length)
		{
			if (line[i] != ' ')
			{
				info->cmds = set_cmds(info, line);
				break ;
			}
			i++;
		}
		if (i == length)
			info->cmds = 0;
	}
}
