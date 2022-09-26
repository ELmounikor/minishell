/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:44:23 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/26 19:17:42 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	output = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!output)
		return (0);
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (s2[j])
		output[i++] = s2[j++];
	output[i] = '\0';
	return (output);
}

char	*ft_strjoin_char(char const *s1, char const *s2, char c)
{
	char	*output;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	output = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!output)
		return (0);
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	output[i++] = c;
	while (s2[j])
		output[i++] = s2[j++];
	output[i] = '\0';
	return (output);
}

void	ft_split_cleaner(char **output)
{
	int	i;

	i = 0;
	while (output[i])
		free(output[i++]);
	free(output);
}

char	*str_edit(char *s)
{
	char	*new_s;
	int		i;
	int		j;

	if (!(s && s[0] == s[ft_strlen(s) - 1] && (s[0] == 34 || s[0] == 39)))
		return (s);
	new_s = (char *) malloc (ft_strlen(s) - 1);
	if (!new_s)
	{
		perror("malloc error");
		exit(0);
	}
	i = 1;
	j = 0;
	while (s[i] && s[i + 1])
		new_s[j++] = s[i++];
	new_s[j] = 0;
	ft_free(&s);
	return (new_s);
}

char	ft_convert(char s, char c)
{
	if (s == -1)
		return (' ');
	if (s == -2)
		return (c);
	return (s);
}
