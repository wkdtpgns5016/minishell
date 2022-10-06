#include "../../includes/minishell.h"

int	is_redir_garbage(char *str)
{
	if (ft_strchr(str, '\"') == 0 && ft_strchr(str, '\'') == 0)
	{
		if (ft_strchr(str, '<') != 0 || ft_strchr(str, '>') != 0)
			return (1);
	}
	return (0);
}

int	count_redir_garbage(char **token)
{
	int		i;
	int		count;
	int		size;
	char	**temp_arr;
	char	*temp;

	i = 0;
	count = 0;
	while (token[i] != 0)
	{
		size = 0;
		if (is_redir_garbage(token[i]))
		{
			temp = make_cmd_redir(token[i]);
			temp_arr = ft_split(temp, ' ');
			ft_free((void **)&temp);
			while (temp_arr[size] != 0)
				size++;
			ft_free_arr((char ***)&temp_arr);
			count += size;
		}
		else
			count++;
		i++;
	}
	return (count);
}

int	insert_divide_redir(char ***arr, char *redir, int index)
{
	char	**divide_redir;
	int		size;
	int		i;

	size = 0;
	i = 0;
	divide_redir = create_divide_redir(redir);
	while (divide_redir[size] != 0)
		size++;
	while (i < size)
	{
		(*arr)[index + i] = ft_strdup(divide_redir[i]);
		i++;
	}
	ft_free_arr(((char ***)&divide_redir));
	return (size);
}

char	**divide_redir_garbage(char **token)
{
	int		count;
	int		i;
	int		j;
	int		size;
	char	**new;

	i = 0;
	j = 0;
	while (token[i] != 0)
		i++;
	size = count_redir_garbage(token);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		if (is_redir_garbage(token[j]))
		{
			insert_divide_redir(&new, token[j], i);
		}
		else
			new[i++] = token[j++];
	}
	return (0);
	// 리다이렉션 붙어 있는 개수 계산
	// 붙어 있는 개수 + token 크기 만큼 배열 할당
	// new[i++] = token[j++] 으로 넣음
	// 넣다가 붙은 리다이렉션을 만나면 그거 쪼개서 new에 넣기
	// 반복


}
