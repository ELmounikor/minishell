/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:10:20 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/24 12:54:34 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(0);
}

t_env	*ft_lstnew_env(char *variable, char *value)
{
	t_env	*l;

	l = (t_env *)malloc(sizeof(t_env));
	if (!l)
		return (0);
	l->variable = ft_strdup(variable);
	l->value = ft_strdup(value);
	l->next = NULL;
	return (l);
}

void	ft_lstadd_front_env(t_env	**alst, t_env *new)
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

t_env	*ft_lstlast_env(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	if (!alst)
		return ;
	if (*alst)
		ft_lstlast_env(*alst)->next = new;
	else
		ft_lstadd_front_env(alst, new);
}
