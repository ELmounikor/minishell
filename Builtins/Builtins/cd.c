/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:02:20 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/16 20:09:29 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_value(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, str, ft_strlen(tmp->variable) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_path_env(t_env *env, char *path)
{
	char	*oldpath;
	char	*cmd;

	oldpath = get_value(env, "PWD");
	ft_remove_element_list(&env, "OLDPWD");
	ft_remove_element_list(&env, "PWD");
	cmd = NULL;
	if (path)
		cmd = ft_strjoin("PWD=", path);
	if (cmd)
	{
		export_element(cmd, env);
		free(cmd);
	}	
	cmd = NULL;
	cmd = ft_strjoin("OLDPWD=", oldpath);
	if (cmd)
	{
		export_element(cmd, env);
		free(cmd);
	}
}

void	get_home(t_env *env)
{
	char	*path;
	int		r;

	path = get_value(env, "HOME");
	if (!path)
	{
		ft_putstr_fd("sh-sm: cd: HOME not set\n", 2);
		g_exit_value = 1;
	}
	else
	{
		r = chdir(path);
		if (r == 0)
			change_path_env(env, path);
	}
}

void	cd(char **argv, t_env *env)
{
	int		r;
	char	*path;

	path = NULL;
	if (argv[1] == NULL)
		get_home(env);
	else if (ft_strncmp(argv[1], "~", ft_strlen(argv[1]) + 1) == 0)
	{
		r = chdir(getenv("HOME"));
		if (r == 0)
			change_path_env(env, getenv("HOME"));
	}
	else
	{
		if (argv[1][0] == '~')
		{
			chdir(getenv("HOME"));
			path = &argv[1][2];
			argv[1] = ft_strdup(path);
		}
		r = chdir(argv[1]);
		if (r == 0)
			change_path_env(env, getcwd(NULL, 0));
		else
		{
			ft_putstr_fd("sh-sm: cd: ", 2);
			if (path)
			{
				ft_putstr_fd(getenv("HOME"), 2);
				ft_putstr_fd("/", 2);
			}
			perror(argv[1]);
			g_exit_value = 1;
		}
	}
}
