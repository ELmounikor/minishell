/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:33:26 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/27 15:06:27 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_builtins(t_cmd *cmd, t_env *env)
{
	if (cmd->args[0])
	{
		if (ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])) == 0)
			print_env(env);
		else if (ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])) == 0)
			echo(cmd->args);
		else
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			//exit(127);
		}
	}
}