/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:02:20 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/25 17:21:25 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	change_pwd_oldpwd(char *pwd, t_data *data)
{
	char	*cmd;
	char	*p;

	if (ft_exist_value(data->env, pwd, NULL) != 0)
	{
		ft_remove_element_list(&data->env, pwd);
		p = ft_strjoin(pwd, "=");
		cmd = ft_strjoin(p, data->pwd);
		export_element(cmd, &data->env);
		if (cmd)
			free(cmd);
		if (p)
			free(p);
	}
}

void	change_pwd_cd(t_data *data, char *path, char *arg)
{
	char	*cmd;

	change_pwd_oldpwd("OLDPWD", data);
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
		if (cmd)
			free(cmd);
	}
	change_pwd_oldpwd("PWD", data);
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
			//if(path)
				//free(path);
		//free(path);
	}
}

void	ft_chdir(char **argv, t_data *data, char *path)
{
	int		r;

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
	if (path)
		free(path);
}

void	cd(char **argv, t_data *data)
{
	int		r;
	char	*path;

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
		path = NULL;
		if (argv[1][0] == '~' && argv[1][1] == '/')
		{
			chdir(getenv("HOME"));
			if (argv[1][2] == '\0')
				return ;
			path = ft_strdup(&argv[1][2]);
			free(argv[1]);
			argv[1] = ft_strdup(path);
		}
		ft_chdir(argv, data, path);
	}
}
