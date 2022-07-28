/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:15:16 by mel-kora          #+#    #+#             */
/*   Updated: 2021/11/22 20:52:40 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_start(char const *s1, char const *set)
{
	int	start;
	int	i;

	start = 0;
	while (s1[start])
	{
		i = 0;
		while (set[i] && s1[start] != set[i])
			i++;
		if (s1[start] != set[i])
			return (start);
		start++;
	}
	return (0);
}

static int	get_end(char const *s1, char const *set)
{
	int	end;
	int	i;

	end = 0;
	while (s1[end])
		end++;
	end--;
	while (end >= 0 && s1[end])
	{
		i = 0;
		while (set[i] && s1[end] != set[i])
			i++;
		if (s1[end] != set[i])
			return (end + 1);
		end--;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*output;
	int		start;
	int		end;
	int		i;

	i = 0;
	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	start = get_start(s1, set);
	end = get_end(s1, set);
	output = (char *) malloc((end - start + 1) * sizeof(char));
	if (!output)
		return (0);
	while (start < end && s1[start])
		output[i++] = s1[start++];
	output[i] = '\0';
	return (output);
}
/*
#include <stdio.h>
int	main()
{
	char *s = "";
	char *set = "";
	printf("%s", ft_strtrim(s,set));
}*/
