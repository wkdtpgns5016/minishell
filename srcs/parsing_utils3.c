/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:02 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/16 18:58:05 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_last_index_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
		i++;
	return (i - 1);
}

int	check_last_pipe(char *line)
{
	char	**arr;
	int		i;

	arr = ft_split(line, ' ');
	if (arr == 0)
		return (-1);
	i = get_last_index_arr(arr);
	if (ft_strncmp(arr[i], "|", ft_strlen(arr[i])) == 0)
	{
		ft_free_arr((char ***)&arr);
		return (1);
	}
	ft_free_arr((char ***)&arr);
	return (0);
}

char	*add_last_cmd(char *str, t_info *info)
{
	char	*temp;
	char	*new;
	char	*add;

	new = str;
	while (check_last_pipe(new))
	{
		temp = new;
		add = readline("> ");
		if (add == 0)
		{
			print_error_message("\rsyntax error", "unexpected end of file");
			if (info->recent_exit_code != 0)
				ft_free((void **)&info->recent_exit_code);
			info->recent_exit_code = (int *)malloc(sizeof(int) * 2);
			info->recent_exit_code[0] = 258;
			info->recent_exit_code[1] = -1;
			return (0);
		}
		new = ft_strjoin(temp, add);
		ft_free((void **)&add);
		ft_free((void **)&temp);
		temp = make_cmd_redir(new);
		ft_free((void **)&new);
		new = make_cmd_pipe(temp);
		ft_free((void **)&temp);
	}
	return (new);
}
