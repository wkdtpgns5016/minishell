#include "../includes/minishell.h"

int	get_index_arr(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != 0)
		i++;
	return (i);
}

char	**remove_redir(char **cmd, int start, int end)
{
	char	**new;
	int		len;
	int		remove_num;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = get_index_arr(cmd);
	remove_num = end - start + 1;
	new = (char **)malloc(sizeof(char *) * (len - remove_num + 1));
	while (j < len - remove_num + 1)
	{
		if (i >= start && i <= end)
			i++;
		else
			new[j++] = cmd[i++];
	}
	new[j] = 0;
	return (new);
}

int main(int ac, char **av, char **envp)
{
	char *str = "a b c d e f";
	char **a = ft_split(str, ' ');

	a = remove_redir(a, 1, 3);
	while (*a != 0)
	{
		printf("%s ", *a);
		a++;
	}
}
