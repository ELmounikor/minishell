/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:02:20 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/20 18:03:23 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_value(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, str, ft_strlen(tmp->variable) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_pwd_cd(t_data *data, char *path, char *arg)
{
	char	*cmd;

	if (ft_exist_value(data->env, "OLDPWD", NULL) != 0)
	{
		ft_remove_element_list(&data->env, "OLDPWD");
		cmd = ft_strjoin("OLDPWD=", data->pwd);
		export_element(cmd, &data->env);
		free(cmd);
	}
	if (data->pwd)
		free(data->pwd);
	if (path)
		data->pwd = ft_strdup(path);
	else
	{
		ft_putstr_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd("getcwd:cannot access parent directories:", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		cmd = ft_strjoin(data->pwd, "/");
		data->pwd = ft_strjoin(cmd, arg);
		free(cmd);
	}
	if (ft_exist_value(data->env, "PWD", NULL) != 0)
	{
		ft_remove_element_list(&data->env, "PWD");
		cmd = ft_strjoin("PWD=", data->pwd);
		export_element(cmd, &data->env);
		free(cmd);
	}
}

void	get_home(t_data *data)
{
	char	*path;
	int		r;

	path = get_value(&data->env, "HOME");
	if (!path)
	{
		ft_putstr_fd("sh-sm: cd: HOME not set\n", 2);
		g_exit_value = 1;
	}
	else
	{
		r = chdir(path);
		if (r == 0)
			change_pwd_cd(data, path, NULL);
	}
}

void	cd(char **argv, t_data *data)
{
	int		r;
	char	*path;

	path = NULL;
	if (argv[1] == NULL)
		get_home(data);
	else if (ft_strncmp(argv[1], "~", ft_strlen(argv[1]) + 1) == 0)
	{
		r = chdir(getenv("HOME"));
		if (r == 0)
			change_pwd_cd(data, getenv("HOME"), argv[1]);
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
			change_pwd_cd(data, getcwd(NULL, 0), argv[1]);
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
