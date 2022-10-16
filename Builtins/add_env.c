/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:33:57 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/27 18:40:26 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*ft_copy_env(t_env *env)
{
	t_env	*copy_env;
	t_env	*tmp;

	tmp = env;
	copy_env = NULL;
	while (tmp)
	{
		ft_lstadd_back_env(&copy_env, ft_lstnew_env(tmp->variable, tmp->value));
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
		if (ft_strncmp(s1, tmp->variable, ft_strlen(s1) + 1) == 0)
		{
			f = ft_strjoin(tmp->value, s2);
			free(tmp->value);
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
			return (1);
		i++;
	}
	return (0);
}

void	add_env(char **f, t_env **envp, char *str)
{
	t_env	*tmp;
	int		size;
	char	*sub;
	int		c;

	tmp = *envp;
	size = ft_strlen(f[0]);
	if (f[0][size - 1] == '+')
	{
		sub = ft_substr(f[0], 0, size - 1);
		add_element(sub, f[1], envp);
	}
	else
	{
		c = ft_exist(str, '=');
		if (ft_strlen(f[1]) == 0 && c == 0)
			ft_lstadd_back_env(envp, ft_lstnew_env(f[0], NULL));
		else
			ft_lstadd_back_env(envp, ft_lstnew_env(f[0], f[1]));
	}
}
