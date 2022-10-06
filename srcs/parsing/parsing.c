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

int	check_syntax(t_info *info, char *line, char **token)
{
	int		flag;

	if (token == 0)
		flag = check_readline(line);
	else
		flag = check_sub_readline(token);
	if (flag != 0)
	{
		if (flag == 1)
		{
			info->recent_exit_code = \
			make_exit_code(&(info->recent_exit_code), 1);
			info->recent_exit_code[0] = 258;
		}
		return (1);
	}
	return (0);
}

t_cmds	*set_cmds(t_info *info, char *line)
{
	t_cmds	*cmd_list;
	char	*temp;
	char	*new;

	info->history_cmd = ft_strdup(line);
	if (info->history_cmd == 0)
		exit(1);
	if (check_syntax(info, line, 0))
		return (0);
	temp = make_cmd_pipe_amd_redir(line);
	new = add_last_cmd(temp, info);
	ft_free((void **)&temp);
	if (new == 0)
		return (0);
	ft_free((void **)&(info->history_cmd));
	info->history_cmd = ft_strdup(new);
	if (info->history_cmd == 0)
		exit(1);
	change_line(&new, info);
	cmd_list = make_cmds(new, info);
	ft_free((void **)&new);
	return (cmd_list);
}

void	set_info(t_info *info, char *line)
{
	int	i;
	int	length;
	char	**arr;

	arr = (char **)malloc(sizeof(char *) * 7);
	arr[0] = ft_strdup("cat");
	arr[1] = ft_strdup("\"ls | $USER\"");
	arr[2] = ft_strdup("<<eof<<<<");
	arr[3] = ft_strdup("|");
	arr[4] = ft_strdup("<<eof");
	arr[5] = ft_strdup("ls");
	arr[6] = ft_strdup("a");
	arr[7] = ft_strdup("\'$USER test\'");
	arr[8] = 0;
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
				divide_redir_garbage(arr);
				info->cmds = set_cmds(info, line);
				// info->cmds = insert_cmds(arr, info);
				break ;
			}
			i++;
		}
		if (i == length)
			info->cmds = 0;
	}
	// t_cmds *temp;
	// temp = info->cmds;
	// while (temp != 0)
	// {
	// 	int i = 0;
	// 	while (temp->cmd[i] != 0)
	// 		printf("%s ",temp->cmd[i++]);
	// 	printf("\n");
	// 	temp = temp->next;
	// }
	// printf("완");
	// getchar();
}
