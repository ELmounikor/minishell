/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:20:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/22 15:43:46 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_readline(char *prompt)
{
	char	*s;

	ft_putstr_fd(prompt, 1);
	s = get_next_line(0);
	if (s)
		s[ft_strlen(s) - 1] = 0;
	return (s);
}

void	ft_free(char **s)
{
	if (*s)
		free(*s);
	*s = NULL;
}

int	ft_reader(int fd, char **s)
{
	int		i;
	int		reader;

	reader = read(fd, *s, 1);
	if (reader <= 0)
	{
		ft_free(s);
		return (-1);
	}
	(*s)[reader] = '\0';
	i = 0;
	while ((*s)[i] && (*s)[i] != '\n')
		i++;
	if ((i < 1 && !(*s)[i]) || (*s)[i] == '\n')
		reader = -1;
	return (reader);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*str;
	char		*temp;
	int			reader;

	line = NULL;
	if (fd < 0)
		return (0);
	reader = 1;
	while (reader > 0)
	{
		str = (char *) malloc(2);
		if (!str)
			return (0);
		reader = ft_reader(fd, &str);
		temp = ft_strjoin(line, str);
		ft_free(&line);
		ft_free(&str);
		line = temp;
	}
	return (line);
}
