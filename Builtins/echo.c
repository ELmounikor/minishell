/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:37:19 by sennaama          #+#    #+#             */
/*   Updated: 2022/11/06 15:47:39 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	verifie_n(char	*argv)
{
	int	i;

	if (ft_strncmp(argv, "-n", ft_strlen(argv) + 1) == 0)
		return (1);
	if (ft_strncmp(argv, "-n", 2) == 0)
	{
		i = 2;
		while (argv[i] == 'n')
			i++;
		if (!argv[i])
			return (1);
		return (0);
	}
	return (0);
}

void	echo(char **argv)
{
	int	i;
	int	n;

	if (argv[1] == NULL)
	{
		printf("\n");
		return ;
	}
	n = 0;
	while (verifie_n(argv[1 + n]) == 1)
		n++;
	i = 1 + n;
	while (argv[i])
	{
		if (argv[i + 1])
			printf("%s ", argv[i]);
		else if (!argv[i + 1] && n != 0)
			printf("%s", argv[i]);
		else if (!argv[i + 1] && n == 0)
			printf("%s\n", argv[i]);
		i++;
	}
}
