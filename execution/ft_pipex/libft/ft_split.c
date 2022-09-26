/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 19:00:34 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/26 14:54:42 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	size_t	size;
	int		i;
	int		j;

	size = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			size++;
		while (s[i] != c && s[i])
			i++;
	}
	return (size);
}

static int	*ft_size_word(char const *s, char c)
{
	int	*sizes;
	int	i;
	int	j;

	sizes = (int *)malloc(ft_count_words(s, c) * sizeof(int));
	if (!sizes)
		return (0);
	i = 0;
	j = 0;
	while (s[j] && i < ft_count_words(s, c))
	{
		sizes[i] = 0;
		while (s[j] == c && s[j])
			j++;
		while (s[j] != c && s[j])
		{
			sizes[i]++;
			j++;
		}
		i++;
	}
	return (sizes);
}	

static char	**allocation_matrice(char const *s, char c)
{
	int		*sizes;
	int		i;
	char	**res;
	int		j;

	sizes = ft_size_word(s, c);
	i = -1;
	res = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (0);
	while (++i < ft_count_words(s, c))
	{
		res[i] = (char *) malloc((sizes[i] + 1) * sizeof(char));
		if (!res[i])
		{
			j = 0;
			while (j < i)
				free(res[j++]);
			free(res);
			free(sizes);
			return (0);
		}
	}
	free(sizes);
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		k;
	int		j;
	char	**res;

	if (!s)
		return (0);
	res = allocation_matrice(s, c);
	if (!res)
		return (0);
	i = 0;
	j = 0;
	k = 0;
	while (s[j] && i < ft_count_words(s, c))
	{
		while (s[j] == c && s[j])
			j++;
		while (s[j] != c && s[j])
			res[i][k++] = s[j++];
		res[i][k] = 0;
		k = 0;
		i++;
	}
	res[i] = 0;
	return (res);
}
