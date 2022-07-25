#include "../includes/minishell.h"

int	check_num_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*get_str_before_redir(char *cmd, char redir)
{
	int		i;
	char	*str;

	i = 0;
	while (cmd[i] != redir)
		i++;
	str = ft_substr(cmd, 0, i - 1);
	if (str == 0)
		return (0);
	return (str);
}

char	*get_str_after_redir(char *cmd, char redir)
{
	int		i;
	char	*str;

	i = 0;
	while (cmd[i] != redir)
		i++;
	if (cmd[i] == '\0')
		return (0);
	else
		str = ft_substr(cmd, i, ft_strlen(cmd) - i);
	return (str);
}
