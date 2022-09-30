/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:40:36 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/30 15:36:05 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"
#include <stdlib.h>

void	ft_wait_child(int *id, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		waitpid(id[i], NULL, 0);
		i++;
	}
}

void	ft_execute_cmd(t_cmd *cmd, int j, t_env *env)
{
	if (ft_builtins(cmd->args[j], cmd, env) == 1)
	{
		cmd->path = ft_get_path(cmd->args[j], env);
		execve(cmd->path, cmd->args, get_env_char(env));
	}
	else
		exit(0);
}

void	ft_pipe(t_cmd **cmd, int nbr_cmd, t_env *env)
{
	int	**fd;
	int	i;
	int	*id;
	int	j;

	if (nbr_cmd > 1)
		fd = pipe_fd(nbr_cmd);
	else if (nbr_cmd == 1 && ft_builtins(cmd[0]->args[0], cmd[0], env) == 0)
		return ;
	id = (int *)malloc((nbr_cmd) * sizeof(int));
	if (!id)
		exit(1);
	i = 0;
	while (cmd[i])
	{
		id[i] = fork();
		if (id[i] == 0)
		{	
			j = ft_dup(cmd[i], i, nbr_cmd, fd);
			ft_execute_cmd(cmd[i], j, env);
		}
		i++;
	}
	ft_close(nbr_cmd - 1, fd);
	ft_wait_child(id, nbr_cmd);
}
