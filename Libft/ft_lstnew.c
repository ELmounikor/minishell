/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:36:15 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/14 20:38:48 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content, int id)
{
	t_list	*element;

	element = (t_list *) malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->content = content;
	element->id = id;
	element->next = NULL;
	return (element);
}

void	lstprint(t_list *input)
{
	t_list	*test;

	test = input;
	while (test)
	{
		printf("id = %d, content = %s\n", test->id, test->content);
		test = test->next;
	}
	printf("(end of list)\n");
}
