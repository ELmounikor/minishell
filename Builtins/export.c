/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:24:00 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/28 18:28:45 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_swap(t_env *tmp1, t_env *tmp2)
{
	char	*var;
	char	*val;

	var = tmp1->variable;
	val = tmp1->value;
	tmp1->variable = tmp2->variable;
	tmp1->value = tmp2->value;
	tmp2->variable = var;
	tmp2->value = val;
}

void	ft_sort_list(t_env **l)
{
	t_env	*tmp1;
	t_env	*tmp2;
	int		r;

	tmp1 = *l;
	while (tmp1->next)
	{
		tmp2 = tmp1;
		while (tmp2)
		{
			r = ft_strncmp(tmp1->variable, tmp2->variable,
					ft_strlen(tmp1->variable) + 1);
			if ((r == 1) || (r == 0 && ft_strncmp(tmp1->value, tmp2->value,
						ft_strlen(tmp1->value) + 1) == 1))
				ft_swap(tmp1, tmp2);
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = ft_copy_env(env);
	ft_sort_list(&tmp);
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->variable, tmp->value);
		else
			printf("declare -x %s\n", tmp->variable);
		tmp = tmp->next;
	}
}

void	export_element(char *cmd, t_env *envp)
{
	char	*sub;
	char	**f;
	int		size;

	f = ft_split_env(cmd, '=');
	size = ft_strlen(f[0]);
	if (f[0][size - 1] == '+')
		sub = ft_substr(f[0], 0, size - 1);
	else
		sub = ft_substr(f[0], 0, size);
	if (!sub || ft_check_variable(sub) == 1)
	{
		ft_putstr_fd("export: \'", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\' : not a valid identifier\n", 2);
		//exit(127);
	}
	else
		add_env(f, &envp, cmd);
}

void	export(char **cmd, t_env *envp)
{
	int		i;

	if (cmd[1] == NULL)
		print_export(envp);
	else
	{
		i = 1;
		while (cmd[i])
		{
			export_element(cmd[i], envp);
			i++;
		}
	}
}
