/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:46:09 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/21 12:46:52 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_list(t_list **l)
{
	t_list	*prev;

	if (*l)
	{
		while (*l)
		{
			prev = *l;
			*l = (*l)->next;
			free(prev);
		}
		*l = NULL;
	}
}

t_list	*ft_lstnew(char *content, int id)
{
	t_list	*l;

	l = (t_list *)malloc(sizeof(t_list));
	if (!l)
		return (0);
	l->content = content;
	l->id =  id;
	l->next = NULL;
	return (l);
}

void	ft_lstadd_front(t_list	**alst, t_list *new)
{
	if (!alst)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	new->next = *alst;
	*alst = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (!alst)
		return ;
	if (*alst)
		ft_lstlast(*alst)->next = new;
	else
		ft_lstadd_front(alst, new);
}

int	ft_lstsize(t_list	*lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

t_list	*ft_list_init(char **argv)
{
	t_list	*l;
	int		i;

	i = 0;
	l =  NULL;
	while (argv[i])
	{
		ft_lstadd_back(&l, ft_lstnew(argv[i], i));
		i++;
	}
	return (l);
} 
char	*get_content(t_list *l, int id)
{
	t_list	*t;

	t = l;
	while (t)
	{
		if (t->id == id)
			return (t->content);
		t = t->next;
	}
	return (NULL);
}