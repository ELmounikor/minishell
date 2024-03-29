/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 21:23:10 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/27 16:07:13 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	arraysize(char const *s, char *c)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = 0;
	while (s && s[i])
	{
		while (s[i] && ft_strchr(c, s[i]))
			i++;
		j = i;
		while (s[i] && !ft_strchr(c, s[i]))
			i++;
		if (j != i)
			size++;
	}
	return (size);
}

static int	*wordsizes(char const *s, char *c)
{
	int	i;
	int	j;
	int	size;
	int	*sizes;

	i = 0;
	size = arraysize(s, c);
	sizes = (int *) malloc((size + 1) * sizeof(int));
	if (!sizes)
		return (0);
	j = 0;
	while (s[i] && j < size)
	{
		while (s[i] && ft_strchr(c, s[i]))
			i++;
		sizes[j] = 0;
		while (s[i] && !ft_strchr(c, s[i]))
		{
			sizes[j]++;
			i++;
		}
		j++;
	}
	sizes[j] = 0;
	return (sizes);
}

static char	**allocation(char const *s, char *c)
{
	char	**output;
	int		size;
	int		*sizes;
	int		i;

	size = arraysize(s, c);
	output = (char **) malloc((size + 1) * sizeof(char *));
	if (!output || !s)
		return (0);
	i = -1;
	sizes = wordsizes(s, c);
	while (++i < size)
	{
		output[i] = (char *) malloc((sizes[i] + 1) * sizeof(char));
		if (!output[i])
		{
			while (i > 0)
				free(output[--i]);
			free(output);
			return (0);
		}
	}
	free(sizes);
	return (output);
}

char	**ft_nsplit(char const *s, char *c)
{
	char	**output;
	int		*sizes;
	int		i;
	int		j;
	int		k;

	output = allocation(s, c);
	if (!output)
		return (0);
	i = -1;
	k = 0;
	sizes = wordsizes(s, c);
	while (++i < arraysize(s, c))
	{
		j = 0;
		while (s[k] && ft_strchr(c, s[k]))
			k++;
		while (j < sizes[i] && s[k] && !ft_strchr(c, s[k]))
				output[i][j++] = s[k++];
		output[i][j] = '\0';
	}
	free(sizes);
	output[i] = NULL;
	return (output);
}
