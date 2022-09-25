/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_temp_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:31:54 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/25 17:31:55 by sehjang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*make_temp_file(void)
{
	char	*filename;
	char	*temp;
	int		temp_number;

	filename = ft_strdup("/tmp/heredoc");
	temp_number = 0;
	while (access(filename, F_OK) == 0)
	{
		ft_free((void **)&filename);
		temp = ft_itoa(temp_number);
		if (temp == 0)
			return (0);
		filename = ft_strjoin("/tmp/heredoc", temp);
		if (filename == 0)
			return (0);
		ft_free((void **)&temp);
		temp_number++;
	}
	return (filename);
}
