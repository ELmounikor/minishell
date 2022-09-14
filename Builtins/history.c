/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:49:40 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/14 13:12:46 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	history_reloader(int ac)
{
	char	*s;
	int		in;

	ac = open("Libft/.sh_history", O_RDWR);
	if (ac > 0)
	{
		in = dup(STDIN_FILENO);
		dup2(ac, STDIN_FILENO);
		close(ac);
		s = readline(NULL);
		while (s)
		{
			add_history(s);
			free(s);
			s = readline(NULL);
		}
		dup2(in, STDIN_FILENO);
		close(in);
	}
}

void	print_history(char *s, unsigned long long n, unsigned long long i)
{
	unsigned long long	j;
	int					h;

	h = open("Libft/.sh_history", O_RDWR, 0666);
	j = 0;
	while (++j <= i - n)
	{
		s = get_next_line(h);
		ft_free(&s);
	}
	s = get_next_line(h);
	while (s)
	{
		printf(" %llu\t%s", i - --n, s);
		ft_free(&s);
		s = get_next_line(h);
	}
	close(h);
}

void	get_history(char *s, long long int n)
{
	unsigned long long	i;
	int					h;

	ft_free(&s);
	h = open("Libft/.sh_history", O_RDWR, 0666);
	if (h < 0)
		return ;
	i = 0;
	s = get_next_line(h);
	while (s && ++i)
	{
		ft_free(&s);
		s = get_next_line(h);
	}
	close(h);
	if ((unsigned long long) n > i || n == -1)
		n = i;
	print_history(s, (unsigned long long) n, i);
}

void	handle_input(char **cmd)
{
	long long int	n;

	n = ft_atoi(cmd[1]);
	if (n < 0)
	{
		printf("sh-sm: %s: -%c: invalid option\n", cmd[0], cmd[1][1]);
		exit(2);
	}
	else
	{
		get_history(cmd[0], n);
		exit(0);
	}
}

void	history(char **cmd)
{
	if (!cmd[1])
		get_history(cmd[0], -1);
	else if (cmd[1])
	{
		if (ft_strncmp(cmd[1], "-c", 3) == 0)
			unlink("Libft/./.sh_history");
		else if (!ft_isnum(cmd[1]))
			printf("sh-sm: %s: %s: : numeric argument required\n", \
			cmd[0], cmd[1]);
		else if (!cmd[2])
			handle_input(cmd);
	}
	else
		printf("sh-sm: %s: too many arguments\n", cmd[0]);
	exit(1);
}
