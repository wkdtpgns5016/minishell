#include "../includes/minishell.h"

void	swap_s(char **s, int p, int c)
{
	char	*temp;

	while (p / 2)
	{
		if (ft_memcmp(s[p / 2], s[c], ft_strlen(s[c]) + 1) < 0 && p / 2 > 0)
			p /= 2;
		else
			break ;
	}
	temp = s[p];
	s[p] = s[c];
	s[c] = temp;
}

void	sort_s(char **s, int len)
{
	int	p;
	int	c;
	int	last_idx;

	last_idx = len;
	while (last_idx)
	{
		p = 1;
		while (p <= last_idx)
		{
			c = p * 2;
			if (c <= last_idx && ft_memcmp(s[p], s[c], ft_strlen(s[p]) + 1) < 0)
				swap_s(s, p, c);
			if (c + 1 <= last_idx && \
				ft_memcmp(s[p], s[c + 1], ft_strlen(s[p]) + 1) < 0)
				swap_s(s, p, c + 1);
			p++;
		}
		s[0] = s[1];
		s[1] = s[last_idx];
		s[last_idx] = s[0];
		last_idx--;
	}
}

void	write_s(char **s)
{
	int	j;
	int	i;

	j = 0;
	while (s[++j])
	{
		i = -1;
		printf("declare -x ");
		while (s[j][++i] && s[j][i] != '=')
			printf("%c", s[j][i]);
		if (s[j][i])
		{
			printf("=\"");
			printf("%s\"", (s[j] + ++i));
		}
		printf("\n");
	}
}
