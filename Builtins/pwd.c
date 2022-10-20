/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 23:12:11 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/20 17:29:02 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd(char *p)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		printf("%s\n", path);
		free(path);
	}
	else if (p)
		printf("%s\n", p);
}
