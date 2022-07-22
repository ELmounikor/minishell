/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:49:40 by mel-kora          #+#    #+#             */
/*   Updated: 2022/07/22 20:16:27 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*write_history(void)
{
	char	*s;
	int		h;

	write(1, "sh-sm$ ", 7);
	s = get_next_line(0);
	h = open("Libft/./.sh_history", O_RDWR | O_APPEND | O_CREAT, 0666);
	write(h, s, ft_strlen(s));
	close(h);
	return (s);
}

void	print_history(char *s, unsigned long long n, unsigned long long i)
{
	unsigned long long	j;
	int					h;

	h = open("Libft/./.sh_history", O_RDWR, 0666);
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

void	get_history(char *s, unsigned long long n)
{
	unsigned long long	i;
	int					h;

	ft_free(&s);
	h = open("Libft/./.sh_history", O_RDWR, 0666);
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
	if (n > i)
		n = i;
	print_history(s, n, i);
}
