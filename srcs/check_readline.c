#include "../includes/minishell.h"

int	is_redir_or_pipe(char *str)
{
	int	flag;

	flag = is_redir(str);
	if (flag)
		return (flag);
	else
	{
		if (*str == '|')
			return (PIPE_LINE);
	}
	return (0);
}

int	check_token(char **token_arr, int i, int flag)
{
	if (flag == PIPE_LINE)
		return (check_pipe(token_arr, i));
	else
		return (check_redir(token_arr, i));
}

int	check_first_token(char *token)
{
	int	check;

	check = 0;
	if (is_include_str(token, "|", ft_strlen(token)) == 0)
	{
		if (is_include_str(token, "||", ft_strlen(token)) == 0)
			check = print_error_message_syntax("||");
		else
			check = print_error_message_syntax("|");
	}
	else if (is_include_str(token, "&", ft_strlen(token)) == 0)
	{
		if (is_include_str(token, "&&", ft_strlen(token)) == 0)
			check = print_error_message_syntax("&&");
		else
			check = print_error_message_syntax("&");
	}
	return (check);
}

int	check_readline(char *line)
{
	char	**token;
	int		i;
	int		flag;
	int		check;

	token = ft_split(line, ' ');
	if (token == 0)
		return (-1);
	i = 0;
	flag = 0;
	check = check_first_token(token[0]);
	while (token[i] != 0)
	{
		if (check)
			break ;
		flag = is_redir_or_pipe(token[i]);
		if (flag)
			check = check_token(token, i, flag);
		i++;
	}
	ft_free_arr((char ***)&token);
	return (check);
}
