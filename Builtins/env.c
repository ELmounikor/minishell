/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:13:57 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/16 20:34:53 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*get_env(char **en)
{
	t_env	*l;
	int		i;
	char	**f;

	if (!en)
		exit(1);
	l = NULL;
	i = 0;
	while (en[i])
	{
		f = ft_split_env(en[i], '=');
		ft_lstadd_back_env(&l, ft_lstnew_env(f[0], f[1]));
		i++;
	}
	l->pwd = NULL;
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
