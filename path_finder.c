/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 12:52:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/27 16:46:10 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
char	**get_paths(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	path = env[i];
	if (!path)
		return (NULL);
	return (ft_split(path + 5, ':'));
}

char	*get_path(char *cmd, char **paths)
{
	char	*abs_path;
	int		i;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (ft_strdup(cmd));
	i = -1;
	while (paths[++i])
	{
		abs_path = ft_strjoin_char(paths[i], cmd, '/');
		if (!access(abs_path, X_OK))
			return (abs_path);
		ft_free(&abs_path);
	}
	return (NULL);
}
*/