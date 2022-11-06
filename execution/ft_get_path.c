/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:38:16 by sennaama          #+#    #+#             */
/*   Updated: 2022/11/06 17:43:40 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"

char	**get_value_devise(t_env *env, char *p)
{
	int		i;
	char	*path;
	char	**mypaths;
	char	*tmp;

	mypaths = NULL;
	path = get_value(&env, p);
	if (path)
	{
		mypaths = ft_split(path, ':');
		i = 0;
		while (mypaths[i])
		{
			tmp = ft_strjoin(mypaths[i], "/");
			free(mypaths[i]);
			mypaths[i] = tmp;
			i++;
		}
		free(path);
	}
	return (mypaths);
}

void	ft_free_char(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	if (p)
		free(p);
}

char	*ft_check_directory(char *arg)
{
	if (arg[0] == '/' || (arg[0] == '.' && arg[1] == '/'))
	{
		if (access(arg, X_OK) == 0)
			return (arg);
		else
		{
			ft_putstr_fd("sh-sm: ", 2);
			perror(arg);
			if (errno == 20 || access(arg, F_OK) == 0)
				exit(126);
			else
				exit(127);
		}
	}
	return (NULL);
}

char	*ft_get_path(char *arg, t_env *env)
{
	int		i;
	char	*path;
	char	**mypaths;
	char	*res;

	i = 0;
	res = ft_check_directory(arg);
	if (res)
		return (res);
	mypaths = get_value_devise(env, "PATH");
	while (mypaths && mypaths[i])
	{
		path = ft_strjoin(mypaths[i], arg);
		if (access(path, 0) == 0)
		{
			ft_free_char(mypaths);
			return (path);
		}
		if (path)
			free(path);
		i++;
	}
	if (mypaths)
		ft_free_char(mypaths);
	return (NULL);
}
