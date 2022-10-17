/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 19:22:51 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/17 11:02:17 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_p(t_list **old_position, t_list **old_next, t_list **token, int *i)
{
	*old_position = (*token);
	*old_next = (*token)->next;
	*i = 0;
}

char	*get_nd_split(t_list **token, char *value)
{
	t_list	*old_position;
	t_list	*old_next;
	char	*s;
	char	**dic;
	int		i;

	set_p(&old_position, &old_next, token, &i);
	dic = ft_nsplit(value, " \t\n");
	if (value && ft_strchr(" \t\n", value[i]))
		i++;
	while (dic && dic[i])
	{
		(*token)->next = ft_lstnew(ft_strdup(dic[i++]), 0);
		*token = (*token)->next;
	}
	(*token) = old_next;
	(*token) = old_position;
	if (value && ft_strchr(" \t\n", value[0]))
	{
		s = ft_strdup(dic[0]);
		ft_split_cleaner(dic);
		return (s);
	}
	ft_split_cleaner(dic);
	return (0);
}
