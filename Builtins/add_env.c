/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:33:57 by sennaama          #+#    #+#             */
/*   Updated: 2022/11/07 09:05:50 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_exist_value(t_env *env, char *variable, char *value)
{
	while (env)
	{
		if (ft_strcmp(env->variable, variable) == 0)
		{
			if (env->value == NULL
				|| (env->value && value))
				return (1);
			else
				return (2);
		}
		env = env->next;
	}
	return (0);
}

t_env	*ft_copy_env(t_env *env)
{
	t_env	*copy_env;
	t_env	*tmp;

	tmp = env;
	copy_env = NULL;
	while (tmp)
	{
		ft_lstadd_back_env(&copy_env,
			ft_lstnew_env(tmp->variable, tmp->value));
		tmp = tmp->next;
	}
	return (copy_env);
}

void	add_element(char *s1, char *s2, t_env **envp)
{
	t_env	*tmp;
	char	*f;

	tmp = *envp;
	while (tmp)
	{
		if (tmp->variable && ft_strncmp(s1,
				tmp->variable, ft_strlen(s1) + 1) == 0)
		{
			f = ft_strjoin(tmp->value, s2);
			ft_free(&tmp->value);
			tmp->value = f;
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back_env(envp, ft_lstnew_env(s1, s2));
}

int	ft_exist(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	add_env(char **f, t_env **envp, int p)
{
	t_env	*tmp;
	int		size;

	tmp = *envp;
	size = ft_strlen(f[0]);
	if (p == 1)
		add_element(f[0], f[1], envp);
	else
		ft_lstadd_back_env(envp, ft_lstnew_env(f[0], f[1]));
}
