/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:33:26 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/22 16:13:45 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_builtins(char *args, t_cmd *cmd, t_data *data, int nbr_cmd)
{
	if (args)
	{
		g_exit_value = 0;
		if (ft_strncmp(args, "env", ft_strlen(args) + 1) == 0)
			print_env(data->env);
		else if (ft_strncmp(args, "echo", ft_strlen(args) + 1) == 0)
			echo(cmd->args);
		else if (ft_strncmp(args, "export", ft_strlen(args) + 1)
			== 0)
			export(cmd->args, &data->env);
		else if (ft_strncmp(args, "unset", ft_strlen(args) + 1)
			== 0)
			unset(cmd->args, &data->env);
		else if (ft_strncmp(args, "pwd", ft_strlen(args) + 1) == 0)
			pwd(data->pwd);
		else if (ft_strncmp(args, "cd", ft_strlen(args) + 1) == 0)
			cd(cmd->args, data);
		else if (ft_strncmp(args, "exit", ft_strlen(args) + 1) == 0)
			ft_exitt(cmd->args, nbr_cmd);
		else if (ft_strncmp(args, "history", ft_strlen(args) + 1) == 0)
			history(cmd->args);
		else
			return (1);
	}
	return (0);
}
