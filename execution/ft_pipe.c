/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:40:36 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/19 18:34:06 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"

void	ft_wait_child(int *id, int nbr)
{
	int	i;
	int	status;

	i = 0;
	while (i < nbr)
	{
		if (waitpid(id[i], &status, 0) != -1 && g_exit_value != 131
			&& g_exit_value != 130)
				g_exit_value = WEXITSTATUS(status);
		i++;
	}
}

void	ft_execute_cmd(t_cmd *cmd, t_data *data, int nbr_cmd)
{
	if (ft_builtins(cmd->args[0], cmd, data, nbr_cmd) == 1)
	{
		cmd->path = ft_get_path(cmd->args[0], data->env);
		if (execve(cmd->path, cmd->args, get_env_char(data->env)) == -1)
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	else
		exit(g_exit_value);
}

void	change_pwd(t_data *data)
{
	char	*path;

	path = get_value(&data->env, "PWD");
	if (path)
	{
		if (ft_strcmp(path, data->pwd) != 0)
		{
			if (data->pwd)
				free(data->pwd);
			data->pwd = ft_strdup(path);
		}
	}
}

void	ft_pipe(t_cmd **cmd, int nbr_cmd, t_data *data)
{
	int	**fd;
	int	i;
	int	*id;

	change_pwd(data);
	if (nbr_cmd == 1 && cmd[0]->fd[0]== 0 && cmd[0]->fd[1] == 0
		&& ft_builtins(cmd[0]->args[0], cmd[0], data, nbr_cmd) == 0)
		return ;
	if (nbr_cmd > 1)
		fd = pipe_fd(nbr_cmd);
	id = (int *)malloc((nbr_cmd) * sizeof(int));
	if (!id)
		exit(1);
	i = 0;
	while (cmd[i])
	{
		signal(SIGQUIT, handler_child);
		signal(SIGINT, handler_child);
		id[i] = fork();
		if (id[i] == 0)
		{	
			signal(SIGINT, handler_sig);
			ft_dup(cmd[i], i, nbr_cmd, fd);
			ft_execute_cmd(cmd[i], data, nbr_cmd);
		}
		i++;
	}
	ft_close(nbr_cmd - 1, fd);
	ft_wait_child(id, nbr_cmd);
}
