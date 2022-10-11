
#include "../../includes/minishell.h"

int	get_index_arr_pipe(char **token, int index)
{
	int	i;

	i = index;
	while (token[i] != 0)
	{
		if (ft_strncmp(token[i], "|", ft_strlen(token[i])) == 0)
			break ;
		i++;
	}
	return (i);
}

char	**divide_arr(char **token, int start, int index)
{
	char	**new_arr;
	int		i;
	int		j;

	i = 0;
	j = start;
	new_arr = (char **)malloc(sizeof(char *) * (index - start + 1));
	if (new_arr == 0)
		return (0);
	while (i < index - start)
		new_arr[i++] = ft_strdup(token[j++]);
	new_arr[i] = 0;
	return (new_arr);
}

int	create_heredoc(char ***cmd, t_cmds *cmds, t_info *info)
{
	int		i;
	int		flag;

	i = -1;
	flag = 1;
	while ((*cmd)[++i] != 0)
	{
		flag = sub_make_heredoc(cmds, info, i, cmd);
		if (flag == 1)
			break ;
		else if (flag == -1)
		{
			ft_free_arr((char ***)cmd);
			return (1);
		}
	}
	return (0);
}

t_cmds	*create_cmds(char ***cmd, t_info *info)
{
	t_cmds	*cmds;

	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (cmds == 0)
		return (0);
	cmds->heredoc_flag = 0;
	cmds->heredoc_filepath = 0;
	if (create_heredoc(cmd, cmds, info))
		return (0);
	cmds->cmd = *cmd;
	cmds->next = 0;
	cmds->pred = 0;
	return (cmds);
}

t_cmds	*insert_cmds(char **token, t_info *info)
{
	t_cmds	*cmds;
	int		i;
	int		index;
	int		size;
	char	**new_cmd;

	i = 0;
	if (check_syntax(info, 0, token))
		return (0);
	cmds = 0;
	size = 0;
	while (token[size] != 0)
		size++;
	while (i < size)
	{
		index = get_index_arr_pipe(token, i);
		new_cmd = divide_arr(token, i, index);
		add_cmd_back(&cmds, create_cmds(&new_cmd, info));
		i = index + 1;
	}
	return (cmds);
}
