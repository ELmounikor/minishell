/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:36:15 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/17 11:21:29 by mel-kora         ###   ########.fr       */
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

void	cmdprint(t_cmd **cmd)
{
	int	i;
	int	j;

	i = 0;
	printf("\n=============cmd data============\n");
	while (cmd && cmd[i])
	{
		printf("---------------------------------\ndata of the command number %d \
		\n//cmd and its argument's list (%d elements):\n", i + 1, cmd[i]->size \
		- 1);
		j = 0;
		while (cmd[i]->args[j])
			printf("%s\n", cmd[i]->args[j++]);
		printf("%s\n", cmd[i]->args[j]);
		printf("//in and out file descriptors:\nin_fd = %d\
		\nout_fd = %d\
		\n<3\n---------------------------------\n", \
		cmd[i]->fd[0], cmd[i]->fd[1]);
		i++;
	}
}
