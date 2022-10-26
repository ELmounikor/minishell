/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:44:23 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/26 16:48:44 by mel-kora         ###   ########.fr       */
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
	if (!output)
		return ;
	while (output[i])
		ft_free(&output[i++]);
	free(output);
}

char	ft_convert(int c)
{
	if (c < 0)
		return (c * -1);
	return (c);
}
