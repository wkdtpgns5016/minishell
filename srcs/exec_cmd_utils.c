#include "../includes/minishell.h"

int	*make_exit_code(int	**arr, int size)
{
	int	*temp;

	temp = *arr;
	/*if (temp != 0)
		ft_free((void **)arr);
	*/
	temp = (int *)malloc(sizeof(int) * (size + 1));
	temp[size] = -1;
	return (temp);
}
