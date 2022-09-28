/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:54:39 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/28 16:54:09 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_nbr_arg(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	ft_err_exit(char **args)
{
	if (ft_isnum(args[1]) == 0)
	{
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(":numeric argument required\n", 2);
		exit(127);
	}
	if (ft_nbr_arg(args) > 2)
	{
		ft_putstr_fd("exit: too many arguments", 2);
		exit(127);
	}
}

void	ft_exitt(char	**args)
{
	int		nb;
	int		err;

	ft_putstr_fd("exit\n", 2);
	if (args[1])
	{
		ft_err_exit(args);
		nb = ft_atoi_exit(args[1], &err);
		if (err == 1)
		{
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(":numeric argument required", 2);
		}
		exit(nb);
	}
	else
		exit (0);
}