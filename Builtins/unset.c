/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:25:10 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/27 17:26:48 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_remove_firt_element(t_env **env, char *var)
{
	t_env	*tmp;

	tmp = *env;
	if (ft_strncmp(tmp->variable, var, ft_strlen(var)) == 0)
	{
		*env = (*env)->next;
		free(tmp);
		return (1);
	}
	return (0);
}

void	ft_remove_element_list(t_env **env, char *var)
{
	t_env	*tmp1;
	t_env	*tmp2;

	if (ft_remove_firt_element(env, var) == 1)
		return ;
	tmp1 = *env;
	tmp2 = tmp1->next;
	while (tmp2->next)
	{
		if (ft_strncmp(tmp2->variable, var, ft_strlen(var)) == 0)
		{
			tmp1->next = tmp2->next;
			free(tmp2);
			return ;
		}
		tmp1 = tmp2;
		tmp2 = tmp2->next;
	}
	if (ft_strncmp(tmp2->variable, var, ft_strlen(var)) == 0)
	{
		tmp1->next = NULL;
		free(tmp2);
	}
}

void	unset(char **argv, t_env *env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_check_variable(argv[i]) == 1)
		{
			ft_putstr_fd("unset: \'", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("\' : not a valid identifier\n", 2);
		}
		else
			ft_remove_element_list(&env, argv[i]);
		i++;
	}
}
