/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:49:31 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/07 11:17:29 by mel-kora         ###   ########.fr       */
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
/*
#include<stdio.h>
int main()
{
	t_list *l1 = ft_lstnew("ddd");
	t_list	*l2 = ft_lstnew("dasas");
	t_list	*l3 = ft_lstnew("ds");
	t_list *new= ft_lstnew("new");
	l1->next = l2;
	l2->next = l3;
	l3->next = new;
	ft_lstclear(&l1, del);
	while(l1)
	{
		printf("%s\n",l1->content);
		l1 = l1->next;
	}
}*/