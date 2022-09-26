/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:24:00 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/26 18:49:09 by sennaama         ###   ########.fr       */
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

t_env	*ft_sort_list(t_env *l)
{
	t_env	*tmp1;
	t_env	*tmp2;
	int		r;

	tmp1 = l;
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
	return (l);
}

void	add_element(char *s1, char *s2, t_env **envp)
{
	t_env	*tmp;
	char	*f;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strncmp(s1, tmp->variable, ft_strlen(s1)) == 0)
		{
			f = ft_strjoin(s2, tmp->value);
			free(tmp->value);
			tmp->value = f;
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back_env(envp, ft_lstnew_env(s1, s2));
}

void	add_env(char **f, t_env **envp)
{
	t_env	*tmp;
	int		size;
	char	*sub;

	tmp = *envp;
	size = ft_strlen(f[0]);
	if (f[0][size - 1] == '+')
	{
		sub = ft_substr(f[0], 0, size - 1);
		add_element(sub, f[1], envp);
	}
	else
		ft_lstadd_back_env(envp, ft_lstnew_env(f[0], f[1]));
}

void	print_export(t_env *tmp)
{
	if (tmp->value != NULL)
		printf("declare -x %s=\"%s\"\n", tmp->variable, tmp->value);
	else
		printf("declare -x %s\n", tmp->variable);
}
/*
void	ft_check_variable(char	**f)
{
	int		size;
	char	*sub;

	size = ft_strlen(f[0]);
	if (f[0][size - 1] == '+')
		sub = ft_substr(f[0], 0, size - 1);
	else
		sub = ft_substr(f[0], 0, size);
	
}
*/
void	export(char **cmd, t_env *envp)
{
	t_env	*tmp;
	char	**f;

	if (cmd[2] == NULL)
	{
		tmp = ft_sort_list(envp);
		while (tmp)
		{
			print_export(tmp);
			tmp = tmp->next;
		}
	}
	else
	{
		f = ft_split_env(cmd[2], '=');
		add_env(f, &envp);
	}
}
