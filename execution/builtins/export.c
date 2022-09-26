/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:24:00 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/26 19:46:37 by sennaama         ###   ########.fr       */
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
					ft_strlen(tmp1->variable));
			if ((r == 1) || (r == 0 && ft_strncmp(tmp1->value, tmp2->value,
						ft_strlen(tmp1->value)) == 1))
				ft_swap(tmp1, tmp2);
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

void	print_export(t_env *tmp)
{
	while (tmp)
	{
		if (tmp->value != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->variable, tmp->value);
		else
			printf("declare -x %s\n", tmp->variable);
		tmp = tmp->next;
	}
}

int	ft_check_variable(char **f)
{
	int		size;
	char	*sub;
	int		i;

	size = ft_strlen(f[0]);
	if (f[0][size - 1] == '+')
		sub = ft_substr(f[0], 0, size - 1);
	else
		sub = ft_substr(f[0], 0, size);
	if ((sub[0] < 'a' || sub[0] > 'z') && (sub[0] < 'A' || sub[0] > 'Z')
		&& (sub[0] != '_'))
		return (1);
	i = 1;
	while (sub[i])
	{
		if ((sub[i] < 'a' || sub[0] > 'z') && (sub[i] < 'A' || sub[i] > 'Z')
			&& (sub[i] < '0' || sub[i] > '9') && (sub[i] != '_'))
			return (1);
		i++;
	}
	return (0);
}

void	export(int argc, char **cmd, t_env *envp)
{
	t_env	*tmp;
	char	**f;
	int		i;

	if (cmd[2] == NULL)
	{
		tmp = ft_copy_env(envp);
		ft_sort_list(&tmp);
		print_export(tmp);
	}
	else
	{
		i = 2;
		while (i < argc)
		{
			f = ft_split_env(cmd[i], '=');
			if (ft_check_variable(f) == 1)
				printf("export: \'%s\' : not a valid identifier\n", cmd[i]);
			else
				add_env(f, &envp);
			i++;
		}
	}
}
