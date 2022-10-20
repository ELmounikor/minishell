/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:49:40 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/20 17:01:54 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	history_reloader(int ac)
{
	char	*s;
	int		in;

	ac = open("/tmp/.sh-sm_history", O_RDWR);
	if (ac > 0)
	{
		in = dup(STDIN_FILENO);
		dup2(ac, STDIN_FILENO);
		close(ac);
		s = get_next_line(0);
		while (s)
		{
			s[ft_strlen(s) - 1] = 0;
			add_history(s);
			free(s);
			s = get_next_line(0);
		}
		dup2(in, STDIN_FILENO);
		close(in);
	}
}

void	print_history(char *s, unsigned long long n, unsigned long long i)
{
	unsigned long long	j;
	int					h;

	h = open("/tmp/.sh-sm_history", O_RDWR, 0666);
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

void	get_history(char *s, long long int n, int outfd)
{
	unsigned long long	i;
	int					h;

	ft_free(&s);
	dup2(outfd, 1);
	h = open("/tmp/.sh-sm_history", O_RDWR, 0666);
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

int	handle_input(char **cmd, int outfd)
{
	long long int	n;

	n = ft_atoi(cmd[1]);
	if (n < 0)
	{
		printf("sh-sm: %s: -%c: invalid option\n", cmd[0], cmd[1][1]);
		return (2);
	}
	else
	{
		get_history(cmd[0], n, outfd);
		return (0);
	}
}

void	history(char **cmd)
{
	int	outfd;

	outfd = dup(1);
	dup2(2, 1);
	if (!cmd[1])
		get_history(cmd[0], -1, outfd);
	else if (cmd[1])
	{
		if (ft_strncmp(cmd[1], "-c", 3) == 0)
			unlink("/tmp/.sh-sm_history");
		else if (!ft_isnum(cmd[1]))
			printf("sh-sm: %s: %s: : numeric argument required\n", \
			cmd[0], cmd[1]);
		else if (!cmd[2])
			g_exit_value = handle_input(cmd, outfd);
		else
			printf("sh-sm: %s: too many arguments\n", cmd[0]);
	}
	else
		g_exit_value = 1;
	dup2(outfd, 1);
	close(outfd);
}
