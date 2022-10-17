/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:24:00 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/17 19:03:42 by sennaama         ###   ########.fr       */
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
			r = ft_strcmp(tmp1->variable, tmp2->variable);
			if ((r > 0) || (r == 0 && ft_strcmp(tmp1->value, tmp2->value) > 0))
				ft_swap(tmp1, tmp2);
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

void	print_export(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
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
	{
		sub = ft_substr(f[0], 0, size);
		if (ft_exist_value(envp, f[0]) == 1)
			ft_remove_element_list(&envp, f[0]);
	}
	printf("----%s %s\n", f[0], f[1]);
	if (!sub || ft_check_variable(f[0]) == 1)
	{
		ft_putstr_fd("sh-sm: export: \'", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\' : not a valid identifier\n", 2);
		g_exit_value = 1;
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
