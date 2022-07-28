/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:53:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/07/26 10:01:09 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd)
{
	printf("exit\n");
	if (!cmd)
		exit(0);
}

char	***parsing(char *s)
{
	char	***data;
	char	**input;
	int		i;

	input = ft_split(s, '|');
	i = 0;
	while (input[i])
	{
		ft_free(&s);
		s = ft_strtrim(input[i], " ");
		ft_free(&input[i]);
		input[i++] = ft_strdup(s);
	}
	ft_free(&s);
	data = (char ***) malloc ((i + 1) * sizeof(char **));
	if (!data)
		return (0);
	data[i] = NULL;
	while (i--)
		data[i] = ft_split(input[i], ' ');
	ft_split_cleaner(input);
	/*
	i = 0;
	while (data[i])
		printf("'%s\n'", data[i++][0]);	input[i++] = ft_strdup(s);
	*/
	return (data);
}

int	main(int ac, char **av, char **env)
{
	char		***cmd;
	char		*s;

	av = NULL;
	while (ac == 1)
	{
		s = write_history();
		s[ft_strlen(s) - 1] = 0;
		cmd = parsing(s);
		ac = 0;
		while (cmd[ac])
		{
			if (ft_strncmp(cmd[ac][0], "exit", 5) == 0)
			{
				ft_free(&s);
				printf("exit\n\n");
				if (!cmd[ac][2])
					exit(0);
			}
			else if (ft_strncmp(cmd[ac][0], "history", 8) == 0)
				history(cmd[ac][0]);
			else
				printf("%s", cmd[ac]);
			ac++;
		}
		ac = 0;
		while (cmd[ac])
			ft_split_cleaner(cmd[ac]);
		free(cmd);
		ac = 1;
	}
	env = NULL;
}
