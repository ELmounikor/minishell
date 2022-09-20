/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:49:40 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/20 15:07:39 by mounikor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void try_delete(char *var, t_list **env_i, t_list *tmp)
{
	t_list	*env;
	char	**dic;
	
	env = *env_i;
	while (env)
	{
		dic = ft_split(env->content, '=');
		if (!ft_strncmp(var, dic[0], ft_strlen(var) + 1))
		{
			ft_split_cleaner(dic);
			if (tmp)
				tmp->next = env->next;
			else
				*env_i = (*env_i)->next;
			tmp = env;
			env = env->next;
			ft_lstdelone(tmp, &free);
			break;
		}
		ft_split_cleaner(dic);
		tmp = env;
		env = env->next;
	}
}

void unset(char **cmd, t_list **env_i)
{
	int exit;
	int i;

	i = 0;
	exit = 0;
	while (cmd[++i])
	{
		if (!(ft_isalnum(cmd[i]) && !ft_isnum(cmd[i])))
		{
			printf("unset: '%s': not valid identifier\n", cmd[i]);
			exit = 1;
		}
		else
			try_delete(cmd[i], env_i, NULL);
	}
	exit(exit);
}

void export(char **cmd, t_list **env_i)
{
	t_list	*env;
	char	**dic;
	int 	exit;
	int 	i;

	i = 0;
	exit = 0;
	env = *env_i;
	while (!cmd[1] && env)
	{
		printf("declare -x %s", env->content);
		env = env->next;
	}
	while (cmd[++i])
	{
		dic = ft_split(cmd[i], '=');
		if (!(ft_isalnum(dic[0]) && !ft_isnum(dic[0])))
		{
			printf("export: '%s': not valid identifier\n", dic[0]);
			exit = 1;
		}
		else if (dic[1])
		{
			try_delete(dic[0], env_i, NULL);
			ft_lstadd_back(env_i, ft_lstnew(cmd[i], 0));
		}
		ft_split_cleaner(dic);
	}
	exit(exit);
}
