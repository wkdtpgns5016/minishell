#include "../../includes/minishell.h"
#include <stdlib.h>

void	ft_lstadd_back_with_dup(t_list **lst, char c)
{
	char	*content;

	content = (char *)malloc(sizeof(char) * 2);
	if (!content)
		exit(1);
	content[0] = c;
	content[1] = 0;
	ft_lstadd_back(lst, ft_lstnew(content));
}

void	delete_quote(t_list **quote)
{
	t_list	*node_cpy;

	node_cpy = *quote;
	*quote = (*quote)->next;
	ft_lstdelone(node_cpy, free);
	node_cpy = ft_lstlast(*quote);
	ft_lstdelone(node_cpy, free);
}

t_list *interpret_quote(char **p_cmd, t_info *info)
{
	char	*cmd;
	char	quote;
	t_list	*quote_lst;

	cmd = *p_cmd;
	quote_lst = NULL;
	quote = *cmd;
	ft_lstadd_back_with_dup(&quote_lst, *cmd);
	while (*++cmd)
	{
		ft_lstadd_back_with_dup(&quote_lst, *cmd);
		if (*cmd == quote)
		{
			if (quote == '"')
				interpret_dollar(&quote_lst, info);
			delete_quote(&quote_lst);
			cmd++;
			break;
		}
	}
	*p_cmd = cmd;
	return (quote_lst);
}

char	*interpret_cmd(char *cmd, t_info *info)
{
	char	*cmd_cpy;
	t_list	*cmd_lst;
	t_list	*cmd_lst_cpy;

	cmd_cpy = cmd;
	cmd_lst = NULL;
	while (*cmd)
	{
		if (*cmd == '"' | *cmd == '\'')
			ft_lstadd_back(&cmd_lst, interpret_quote(&cmd, info));
		else
			ft_lstadd_back_with_dup(&cmd_lst, *cmd);
		cmd++;
	}
	free(cmd_cpy);
	cmd = (char *)malloc(sizeof(char) * (ft_lstsize(cmd_lst) + 1));
	cmd_cpy = cmd;
	cmd_lst_cpy = cmd_lst;
	while (cmd_lst)
	{
		*cmd++ = *(char *)cmd_lst->content;
		cmd_lst = cmd_lst->next;
	}
	*cmd = 0;
	ft_lstclear(&cmd_lst_cpy, free);
	return (cmd_cpy);
}

void	interpret_cmds(t_cmds *cmds, t_info *info)
{
	int	idx;

	while (cmds)
	{
		idx = -1;
		while (cmds->cmd[++idx])
			cmds->cmd[idx] = interpret_cmd(cmds->cmd[idx], info);
		cmds = cmds->next;
	}
}
