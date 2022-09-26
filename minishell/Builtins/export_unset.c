/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:49:40 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/24 18:16:44 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	try_unset(char *var, t_list **env_i, t_list *tmp)
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
			break ;
		}
		ft_split_cleaner(dic);
		tmp = env;
		env = env->next;
	}
}

void	unset(char **cmd, t_list **env_i)
{
	int	exit_code;
	int	i;

	i = 0;
	exit_code = 0;
	while (cmd[++i])
	{
		if (!(ft_isalnumstr(cmd[i]) && !ft_isnum(cmd[i])))
		{
			printf("unset: '%s': not valid identifier\n", cmd[i]);
			exit_code = 1;
		}
		else
			try_unset(cmd[i], env_i, NULL);
	}
	exit(exit_code);
}

void	try_export(char **cmd, t_list **env_i, int *exit_code)
{
	char	**dic;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		dic = ft_split(cmd[i], '=');
		if (!(ft_isalnumstr(dic[0]) && !ft_isnum(dic[0])))
		{
			printf("export: '%s': not valid identifier\n", dic[0]);
			*exit_code = 1;
		}
		else if (dic[1])
		{
			try_unset(dic[0], env_i, NULL);
			ft_lstadd_back(env_i, ft_lstnew(cmd[i], 0));
		}
		ft_split_cleaner(dic);
	}
}

void	export_(char **cmd, t_list **env_i)
{
	t_list	*env;
	int		exit_code;

	exit_code = 0;
	env = *env_i;
	while (!cmd[1] && env)
	{
		printf("declare -x %s\n", env->content);
		env = env->next;
	}
	try_export(cmd, env_i, &exit_code);
	exit(exit_code);
}
