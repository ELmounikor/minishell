/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outils_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:35:42 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/10 14:36:26 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"

int	**pipe_fd(int nbr_cmd)
{
	int	**fd;
	int	i;

	fd = (int **) malloc((nbr_cmd - 1) * sizeof(int *));
	if (!fd)
		exit(1);
	i = 0;
	while (i < nbr_cmd - 1)
	{
		fd[i] = (int *)malloc(2 * sizeof(int));
		if (!fd[i])
			exit(1);
		i++;
	}
	i = 0;
	while (i < nbr_cmd - 1)
	{
		if (pipe(fd[i]) < 0)
			exit(1);
		i++;
	}
	return (fd);
}

void	ft_close(int argc, int **fd)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

char	**get_env_char(t_env *env)
{
	int		size;
	char	**str;
	int		i;
	char	*join;

	size = ft_envsize(env);
	str = (char **) malloc((size + 1) * sizeof(char *));
	if (!str)
		exit(1);
	i = 0;
	while (env)
	{
		join = ft_strjoin(env->variable, "=");
		str[i] = ft_strjoin(join, env->value);
		i++;
		env = env->next;
	}
	str[i] = 0;
	return (str);
}

int	ft_dup(t_cmd *cmd, int i, int nbr_cmd, int **fd)
{
	int	j;

	j = 0;
	if (cmd->fd[0] < 0)
		exit(1);
	else if (cmd->fd[0] > 0)
	{
		dup2(cmd->fd[0], STDIN_FILENO);
		j++;
	}
	else if (i > 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (cmd->fd[1] < 0)
		exit(1);
	else if (cmd->fd[1] > 0)
		dup2(cmd->fd[1], STDOUT_FILENO);
	else if (i < nbr_cmd - 1)
		dup2(fd[i][1], STDOUT_FILENO);
	ft_close(nbr_cmd - 1, fd);
	return (j);
}
