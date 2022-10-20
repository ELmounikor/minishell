/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:38:16 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/20 14:12:46 by sennaama         ###   ########.fr       */
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
	int	size;

	size = 0;
	while (p[size])
		size++;
	i = size - 1;
	while (i >= 0)
		free(p[i--]);
	free(p);
}

char	*ft_get_path(char *arg, t_env *env)
{
	int		i;
	char	*path;
	char	**mypaths;

	i = 0;
	if (access(arg, 0) == 0 && arg[0] == '/')
		return (arg);
	mypaths = get_value_devise(env, "PATH");
	while (mypaths && mypaths[i])
	{
		path = ft_strjoin(mypaths[i], arg);
		if (access(path, 0) == 0)
		{
			ft_free_char(mypaths);
			return (path);
		}
		free(path);
		i++;
	}
	if (mypaths)
		ft_free_char(mypaths);
	return (NULL);
}
