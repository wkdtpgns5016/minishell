#include "../includes/minishell.h"

char	**make_heredoc(char *content)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(content, ' ');
	if (cmd == 0)
		return (0);
	while (cmd[i] != 0)
	{
		if (ft_strncmp(cmd[i], "<<", 2) == 0)
		{
			get_heredoc(cmd[i + 1]);
			ft_free((void **)&cmd[i]);
			ft_free((void **)&cmd[i + 1]);
			cmd[i] = ft_strdup("<");
			cmd[i + 1] = ft_strdup("here_doc");
		}
		i++;
	}
	i = 0;
	return (cmd);
}
