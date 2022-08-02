#include "../includes/minishell.h"

int	is_redir(char *c)
{
	if (*c == '<' && *(c + 1) != '<')
		return (1);
	else if (*c == '<' && *(c + 1) == '<')
		return (2);
	else if (*c == '>' && *(c + 1) != '>')
		return (3);
	else if (*c == '>' && *(c + 1) == '>')
		return (4);
	return (0);
}

int	get_index_redir(char *temp, int index)
{
	int	i;

	i = index;
	while (*(temp + i) != '\0')
	{
		if (is_redir(temp + i))
			break ;
		i++;
	}
	if (i == (int)ft_strlen(temp))
		return (-1);
	return (i);
}

char	*add_str_between_space(char	*str, char *new, int redir)
{
	char	*result;
	char	*temp;

	result = ft_strjoin(str, new);
	temp = result;
	result = ft_strjoin(temp, " ");
	ft_free((void **)&temp);
	temp = result;
	if (redir == 1)
		result = ft_strjoin(temp, "<");
	if (redir == 2)
		result = ft_strjoin(temp, "<<");
	if (redir == 3)
		result = ft_strjoin(temp, ">");
	if (redir == 4)
		result = ft_strjoin(temp, ">>");
	ft_free((void **)&temp);
	temp = result;
	result = ft_strjoin(temp, " ");
	ft_free((void **)&temp);
	return (result);
}

char	*sub_make_cmd(char *cmd, char *content, int *i, int *j)
{
	char	*str;
	char	*temp;
	char	*new;

	str = cmd;
	while (*j < (int)ft_strlen(content))
	{
		*i = get_index_redir(content, *j);
		if (*i < 0)
			break ;
		temp = str;
		new = ft_substr(content, *j, *i - *j);
		str = add_str_between_space(temp, new, is_redir(content + *i));
		ft_free((void **)&temp);
		ft_free((void **)&new);
		if (is_redir(content + *i) % 2 == 0)
			*j = *i + 2;
		else
			*j = *i + 1;
	}
	return (str);
}

char	*make_cmd_redir(char *content)
{
	char	*cmd;
	char	*temp;
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = get_index_redir(content, j);
	if (i < 0)
		return (ft_strdup(content));
	new = ft_substr(content, j, i - j);
	cmd = add_str_between_space("", new, is_redir(content + i));
	ft_free((void **)&new);
	if (is_redir(content + i) % 2 == 0)
		j = i + 2;
	else
		j = i + 1;
	cmd = sub_make_cmd(cmd, content, &i, &j);
	temp = cmd;
	cmd = ft_strjoin(temp, content + j);
	ft_free((void **)&temp);
	return (cmd);
}
