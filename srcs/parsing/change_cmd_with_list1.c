/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_cmd_with_list1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehjang <sehjang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:58:10 by sehjang           #+#    #+#             */
/*   Updated: 2022/09/26 01:59:53 by sunwchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
/*
char	*change_dollar(char *dollar, t_list *evl)
{
	int	idx;

	idx = 0;
	while (dollar[idx])
	{
		if (!(ft_isalnum((int)dollar[idx]) || dollar[idx] == '_'))
		{
			*dollar = 0;
			break ;
		}
		idx++;
	}
	while (evl)
	{
		if (check_envl(evl->content, dollar))
			return (evl->content);
		evl = evl->next;
	}
	return (" ");
}

char	*make_new_cmd(char *cmd, char *env, int org_size)
{
	int		env_size;
	int		total;
	char	*new_cmd;
	int		idx;

	env_size = 0;
	env = ft_strchr(env, '=');
	if (env)
		env_size = ft_strlen(++env);
	total = ft_strlen(cmd) + env_size - org_size;
	new_cmd = (char *)malloc(sizeof(char) * (total + 1));
	if (!new_cmd)
		return (NULL);
	new_cmd[total] = 0;
	idx = 0;
	while (*cmd != '$')
		new_cmd[idx++] = *(cmd++);
	cmd += org_size + 1;
	if (env)
		while (*env)
			new_cmd[idx++] = *(env++);
	while (*cmd)
		new_cmd[idx++] = *(cmd++);
	return (new_cmd);
}

char *dollar2env(char *cmd, t_info *info)
{
	char	*dollar;
	char	*new_cmd;
	int		i;

	dollar = ft_strdup(ft_strchr(cmd, '$') + 1);
	i = 0;
	while (info->recent_exit_code[i] >= 0)
		i++;
	if (!dollar)
		exit(1);
	else if (*dollar == '?')
		new_cmd = ft_itoa(info->recent_exit_code[i - 1]);
	else
		new_cmd = make_new_cmd(cmd, change_dollar(dollar, \
			info->ev.evl), ft_strlen(dollar));
	if (!new_cmd)
		exit (1);
	free(dollar);
	return (cmd);
}

void	pipestatus(char **cmd, int *status)
{
	char	*main;
	char	*sub1;
	char	*sub2;

	main = ft_itoa(*status);
	sub1 = main;
	while (*++status >= 0)
	{
		sub2 = ft_strjoin(" ", ft_itoa(*status));
		main = ft_strjoin(sub1, sub2);
		free(sub1);
		free(sub2);
		sub1 = main;
	}
	*cmd = main;
}

int	ft_strlen_in_quotes(char *cmd)
{
	int strlen_in_quotes;

	strlen_in_quotes = 0;
	while (*cmd && *cmd != '"')
	{
		strlen_in_quotes++;
		cmd++;
	}
	if (!*cmd)
		return (0);
	while (*cmd && *cmd != '$')
	{
		strlen_in_quotes++;
		cmd++;
	}
	if (!*cmd)
		return (0);
	while (*cmd && *cmd != '"')
	{
		strlen_in_quotes++;
		cmd++;
	}
	if (!*cmd)
		return (0);
	return (strlen_in_quotes);
}

void	quotes2env(char **cmd, t_info *info)
{
	int	strlen;
	char *new_cmd;
	char *org_cmd;

	while (ft_strlen_in_quotes(*cmd));
	{
		org_cmd = *cmd
		while (**cmd != '"')
			(*cmd)++;
		new_cmd = dollar2env(*cmd, info);
		**cmd = 0;
		*cmd = ft_strjoin(org_cmd, new_cmd);
		free(org_cmd);
		free(new_cmd);
	}
	org_cmd = *cmd;
	*cmd = (char *)malloc(sizeof(char) * (ft_strlen(org_cmd) - 1));
	if (!*cmd)
		exit (1);
	while (*org_cmd != '"')
		*(*cmd++) = *(org_cmd++);
	org_cmd++;
	while (*org_cmd != '$')
		*(*cmd++) = *(org_cmd++);
	org_cmd++;
	while (!*org_cmd)
		*(*cmd++) = *(org_cmd++);
	**cmd = 0;
}

void	change_cmd(char **cmd, t_info *info)
{
	char *new_cmd;

	while (*cmd)
	{
		if (ft_strlen_in_quotes(*cmd))
			quotes2env(cmd, info);
		else if (ft_strchr(*cmd, '$'))
		{
			if (!ft_memcmp(*cmd, "${PIPESTATUS[@]}", ft_strlen(*cmd)))
				pipestatus(cmd, info->recent_exit_code);
			else
			{
				new_cmd = dollar2env(*cmd, info);
				free(*cmd);
				*cmd = new_cmd;
			}
		}
		else
			cmd++;
	}
}*/

char	*we_meet_char(char *cmd, t_list **cmd_char_list)
{
	char *new_char;
	t_list	*new_node;

	new_char = (char *)malloc(sizeof(char) * 2);
	if (!new_char)
		exit(1);
	new_char[0] = *cmd;
	new_char[1] = '\0';
	new_node = ft_lstnew(new_char);
	if (!new_char)
		exit(1);
	ft_lstadd_back(cmd_char_list, new_node);
	cmd++;
	return (cmd);
}

void	change_first_node(t_list **first_node)
{
	t_list *temp;

	temp = *first_node;
	*first_node = (*first_node)->next;
	free(temp->content);
	free(temp);
}

char	*we_meet_quotes(char *cmd, t_info *info, t_list **cmd_char_list)
{
	int	dollar_is_here;
	t_list	*quotes;

	dollar_is_here = 0;
	quotes = NULL;
	cmd = we_meet_char(cmd, &quotes);
	while (*cmd)
	{
		if (*cmd == '$')
		{
			cmd = we_meet_dollar(cmd, info, &quotes);
			dollar_is_here++;
		}
		else if(*cmd == '"')
		{
			if (!dollar_is_here)
				cmd = we_meet_char(cmd, &quotes);
			break;
		}
		else
			cmd = we_meet_char(cmd, &quotes);
	}
	if (dollar_is_here && *cmd == '"')
	{
		change_first_node(&quotes);
		cmd++;
	}
	ft_lstadd_back(cmd_char_list, quotes);
	return (cmd);
}

char	*we_meet_dollar(char *cmd, t_info *info, t_list **cmd_char_list)
{
	t_list	*add_node;
	t_list	*dollar;

	add_node = NULL;
	dollar = NULL;
	cmd = we_meet_char(cmd, &dollar);
	while (*cmd)
	{
		if (*cmd == '$')
			cmd = we_meet_dollar(cmd, info, &dollar);
		//else if(*cmd == '"')
		//	cmd = we_meet_quotes(cmd, info, &dollar);
		if(ft_isalnum(*cmd) || *cmd == '_')
			cmd = we_meet_char(cmd, &dollar);
		else
			break ;
	}
	change_node(&dollar, info);
	ft_lstadd_back(cmd_char_list, dollar);
	return (cmd);
}

t_list *cmd2list(char *cmd, t_info *info)
{
	t_list	*cmd_char_list;

	cmd_char_list = NULL;
	while (*cmd)
	{
		if (*cmd == '$')
			cmd = we_meet_dollar(cmd, info, &cmd_char_list);
		else if (*cmd == '"') 
			cmd = we_meet_quotes(cmd, info, &cmd_char_list);	
		else
			cmd = we_meet_char(cmd, &cmd_char_list);	
	}
	return (cmd_char_list);
}

char	*list2cmd(t_list **first_node)
{
	char	*dollar;
	int		idx;

	dollar = (char *)malloc(sizeof(ft_lstsize(*first_node)));
	if (!dollar)
		exit (1);
	idx = 0;
	while (*first_node)
	{
		dollar[idx] = *(char *)((*first_node)->content);
		change_first_node(first_node);
		idx++;
	}
	dollar[idx] = '\0';
	return (dollar);
}

void	change_cmd(char **cmd, t_info *info)
{
	t_list	*cmd_char_list;
	
	while (*cmd)
	{
		cmd_char_list = cmd2list(*cmd, info);
		free(*cmd);
		*cmd = list2cmd(&cmd_char_list);
		cmd++;
	}
}
