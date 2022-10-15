/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:38:16 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/15 17:36:15 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"

char	**get_value_devise(t_env *env, char *p)
{
	int		i;
	char	*str;
	char	*path;
	char	**mypaths;
	char	*tmp;

	str = NULL;
	mypaths = NULL;
	str = get_value(env, p);
	if (str != NULL)
	{
		path = ft_substr(str, 5, ft_strlen(str));
		mypaths = ft_split(path, ':');
		i = 0;
		while (mypaths[i])
		{
			tmp = ft_strjoin(mypaths[i], "/");
			free(mypaths[i]);
			mypaths[i] = tmp;
			i++;
		}
		i = 0;
		free(path);
	}
	return (mypaths);
}

void	ft_free_char(char **p)
{
	int	i;

	i = 0;
	while (p[i])
		free(p[i++]);
	free(p);
}

char	*ft_get_path(char *arg, t_env *env)
{
	int		i;
	char	*path;
	char	**mypaths;

	i = 0;
	if (access(arg, 0) == 0)
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
