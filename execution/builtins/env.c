/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:13:57 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/26 18:14:54 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*ft_lstnew_env(char *variable, char *value)
{
	t_env	*l;

	l = (t_env *)malloc(sizeof(t_env));
	if (!l)
		return (0);
	l->variable = variable;
    l->value = value;
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

t_env	*get_env(char **en)
{
	t_env	*l;
	int		i;
	char	**f;

	l = NULL;
	i = 0;
	while (en[i])
	{
		f = ft_split(en[i], '=');
		ft_lstadd_back_env(&l, ft_lstnew_env(f[0], f[1]));
		i++;
	}	
	return (l);
}

void	print_env(t_env	*env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}
