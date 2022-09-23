/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:29:52 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/21 12:29:53 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
