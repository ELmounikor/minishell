/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:33:26 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/08 19:38:34 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_builtins(char *args, t_cmd *cmd, t_env *env, int nbr_cmd)
{
	if (args)
	{
		g_exit_value = 0;
		if (ft_strncmp(args, "env", ft_strlen(args)) == 0)
			print_env(env);
		else if (ft_strncmp(args, "echo", ft_strlen(args)) == 0)
			echo(cmd->args);
		else if (ft_strncmp(args, "export", ft_strlen(args))
			== 0)
			export(cmd->args, env);
		else if (ft_strncmp(args, "unset", ft_strlen(args))
			== 0)
			unset(cmd->args, env);
		else if (ft_strncmp(args, "pwd", ft_strlen(args)) == 0)
			pwd();
		else if (ft_strncmp(args, "cd", ft_strlen(args)) == 0)
			cd(cmd->args, env);
		else if (ft_strncmp(args, "exit", ft_strlen(args)) == 0)
			ft_exitt(cmd->args, nbr_cmd);
		else
			return (1);
	}
	return (0);
}
