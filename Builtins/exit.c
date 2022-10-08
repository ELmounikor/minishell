/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:54:39 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/08 19:46:02 by sennaama         ###   ########.fr       */
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

int	ft_err_exit(char **args, int i)
{
	if (ft_isnum(args[i]) == 0)
	{
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if ((ft_nbr_arg(args) > 2) && (i == 1))
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_exit_value = 1;
		return (1);
	}
	return (0);
}

void	ft_exitt(char	**args, int nbr_cmd)
{
	int		nb;
	int		err;
	int		i;

	if (nbr_cmd == 1)
		ft_putstr_fd("exit\n", 2);
	i = 1;
	if (args[1] && ft_strncmp(args[1], "--", ft_strlen(args[1]) + 1) == 0
		&& ft_nbr_arg(args) == 3)
		i++;
	nb = 1;
	if (args[i])
	{
		if (ft_err_exit(args, i) == 1)
			return ;
		nb = ft_atoi_exit(args[i], &err);
		if (err == 1)
		{
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	exit(nb);
}
