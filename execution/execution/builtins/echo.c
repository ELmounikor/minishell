/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:37:19 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/26 22:26:47 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo(char **argv)
{
	int	i;
	int	n;

	if (ft_strncmp(argv[2], "-n", 2) == 0)
		n = 1;
	else
		n = 0;
	i = 2 + n;
	while (argv[i + 1])
	{
		printf("%s ", argv[i]);
		i++;
	}
	if (n == 1)
		printf("%s", argv[i]);
	else
		printf("%s\n", argv[i]);
}
