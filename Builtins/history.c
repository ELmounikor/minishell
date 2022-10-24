/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:49:40 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/24 18:49:58 by mel-kora         ###   ########.fr       */
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
		s = ft_readline(0);
		while (s)
		{
			add_history(s);
			ft_free(&s);
			s = ft_readline(0);
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

void	get_shsm_history(long long int n, int outfd)
{
	unsigned long long	i;
	int					h;
	char				*s;

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

void	option_checker(char **cmd)
{
	int	i;

	if (ft_strncmp(cmd[1], "-c", 3) == 0)
	{
		unlink("/tmp/.sh-sm_history");
		rl_clear_history();
	}
	else
	{
		i = 0;
		while (cmd[1][++i] == 'c')
			;
		printf("sh-sm: %s: -%c: invalid option\n", cmd[0], cmd[1][i]);
		g_exit_value = 2;
	}
}

void	history(char **cmd)
{
	int	outfd;

	outfd = dup(1);
	dup2(2, 1);
	if (!cmd[1])
		get_shsm_history(-1, outfd);
	else
	{
		if (cmd[1][0] == '-')
			option_checker(cmd);
		else if (!ft_isnum(cmd[1]))
			printf("sh-sm: %s: %s: : numeric argument required\n", \
			cmd[0], cmd[1]);
		else if (!cmd[2])
			get_shsm_history(ft_atoi(cmd[1]), outfd);
		else
		{
			printf("sh-sm: %s: too many arguments\n", cmd[0]);
			g_exit_value = 1;
		}
	}
	dup2(outfd, 1);
	close(outfd);
}
