/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:22:51 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/27 17:17:41 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_p(t_list **old_pos, t_list **old_next, t_list **token)
{
	*old_pos = (*token);
	*old_next = (*token)->next;
	return (" \t\n");
}

void	reset_p(t_list *old_pos, t_list *old_next, t_list **token, int i)
{
	(*token)->next = old_next;
	(*token) = old_pos;
	if (i > 1)
		(*token)->id = 0;
}

char	*get_nd_split(t_list **token, char *value, int i)
{
	t_list	*old_position;
	t_list	*old_next;
	char	**dic;
	char	*s;

	s = set_p(&old_position, &old_next, token);
	dic = ft_nsplit(value, s);
	if (value && !ft_strchr(s, value[i]))
		i++;
	while (dic && dic[i])
	{
		(*token)->next = ft_lstnew(ft_strdup(dic[i++]), 0);
		*token = (*token)->next;
	}
	if (value && !ft_strchr(s, value[ft_strlen(value) - 1]))
		(*token)->id = old_position->id;
	reset_p(old_position, old_next, token, i);
	if (value && !ft_strchr(s, value[0]))
	{
		s = ft_strdup(dic[0]);
		ft_split_cleaner(dic);
		return (s);
	}
	ft_split_cleaner(dic);
	return (0);
}

int	quote_check(char *s)
{
	int	flag[3];

	flag[0] = -1;
	flag[1] = 0;
	flag[2] = 0;
	while (s && s[++flag[0]])
	{
		if (s[flag[0]] == 34 && flag[1] % 2 == 0)
			flag[2]++;
		else if (s[flag[0]] == 39 && flag[2] % 2 == 0)
			flag[1]++;
	}
	if (flag[2] % 2 == 0 && flag[1] % 2 == 0)
		return (1);
	else
		return (0);
}

void	free_cmds(t_cmd **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = -1;
	while (cmd[++i])
	{
		ft_split_cleaner(cmd[i]->args);
		if (cmd[i]->fd[0] > 0)
			close(cmd[i]->fd[0]);
		if (cmd[i]->fd[1] > 0)
			close(cmd[i]->fd[1]);
		free(cmd[i]);
	}
	free(cmd);
	cmd = NULL;
}
