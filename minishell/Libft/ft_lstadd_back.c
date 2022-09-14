/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:22:17 by mel-kora          #+#    #+#             */
/*   Updated: 2022/08/21 15:42:26 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (*lst)
		(ft_lstlast(*lst))->next = new;
	else
		ft_lstadd_front(lst, new);
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
	ft_lstadd_back(&l1,new);
	while(l1)
	{
		printf("%s\n",l1->content);
		l1 = l1->next;
	}
}*/
