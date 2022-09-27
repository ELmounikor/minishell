/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:02:20 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/27 18:48:43 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_value(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, str, ft_strlen(tmp->variable) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	cd(char **argv, t_env *env)
{
	char	*path;

	(void)env;
	if (argv[1] == NULL || ft_strncmp(argv[1], "~", ft_strlen(argv[1])) == 0)
	{
		path = get_value(env, "HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			//exit(127);
		}
		else
			chdir(path);
	}
	else if (chdir(argv[1]) != 0)
		ft_perror(argv[1]);
}
