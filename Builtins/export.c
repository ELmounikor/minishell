/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:24:00 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/21 17:30:56 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

void	ft_add_export_element(char **f, t_env **envp)
{
	char	*sub;
	int		p;

	p = ft_strlen(f[0]);
	if (f[0][p - 1] != '+')
	{
		p = ft_exist_value(*envp, f[0], f[1]);
		if (p == 1)
			ft_remove_element_list(envp, f[0]);
		else if (p == 2)
			return ;
		p = 0;
	}
	else
	{
		sub = ft_substr(f[0], 0, p - 1);
		free(f[0]);
		f[0] = sub;
		p = 1;
	}
	add_env(f, envp, p);
}

void	ft_check_error_export(char **f, int i, char *cmd)
{
	char	*sub;

	sub = NULL;
	if (f[0])
	{
		if (i > 0 && f[0][i - 1] == '+')
			sub = ft_substr(f[0], 0, ft_strlen(f[0]) - 1);
		else
			sub = ft_strdup(f[0]);
	}
	if (!sub || ft_check_variable(sub) == 1)
	{
		ft_putstr_fd("sh-sm: export: \'", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\' : not a valid identifier\n", 2);
		g_exit_value = 1;
		return ;
	}
}

void	export_element(char *cmd, t_env **envp)
{
	char	**f;
	int		i;

	f = ft_split_env(cmd, '=');
	i = ft_exist(cmd, '=');
	if (i == 0)
		f[1] = NULL;
	ft_check_error_export(f, i, cmd);
	ft_add_export_element(f, envp);
}

void	export(char **cmd, t_env **envp)
{
	int		i;

	if (cmd[1] == NULL)
		print_export(*envp);
	else
	{
		i = 1;
		while (cmd[i])
		{
			if (cmd[i][0] != '=')
				export_element(cmd[i], envp);
			else
			{
				ft_putstr_fd("sh-sm: export: \'", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putstr_fd("\' : not a valid identifier\n", 2);
				g_exit_value = 1;
			}
			i++;
		}
	}
}
