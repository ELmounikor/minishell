/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:49:31 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/26 22:15:20 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst);
		*lst = (*lst)->next;
		if (del && tmp->content)
			del(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}

void	ft_envclear(t_env **lst, void (*del)(void*))
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst);
		*lst = (*lst)->next;
		if (del && tmp->variable)
			del(tmp->variable);
		if (del && tmp->value)
			del(tmp->value);
		free(tmp);
	}
	*lst = NULL;
}
