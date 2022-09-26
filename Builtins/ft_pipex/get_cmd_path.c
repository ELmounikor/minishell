/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:22:46 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/24 17:12:59 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char	**envp)
{
	char	*str;
	int		i;

	i = 0;
	while (envp[i])
	{
		str = ft_strnstr(envp[i], "PATH", ft_strlen(envp[i]));
		if (str != NULL)
			break ;
		i++;
	}
	return (str);
}

char	**get_all_path()
{
	int		i;
	char	*str;
	char	*path;
	char	**mypaths;
	char	*tmp;

	str = NULL;
	mypaths = NULL;
	str = getenv("PATH");
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

char	*get_cmd_path(char	*arg)
{
	int		i;
	char	*path;
	char	**mypaths;

	i = 0;
	mypaths = get_all_path();
	while (mypaths[i])
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
	ft_free_char(mypaths);
	return (NULL);
}
