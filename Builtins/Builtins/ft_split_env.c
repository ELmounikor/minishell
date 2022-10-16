/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:28:43 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/26 18:29:29 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	*count_words(char	*str, char c)
{
	int	*t;
	int	i;

	i = 0;
	t = (int *)malloc(2 * sizeof(int));
	if (!t)
		ft_perror("malloc");
	t[0] = 0;
	t[1] = 0;
	while (str[i] != c && str[i])
	{
		t[0]++;
		i++;
	}
	if (str[i] == '=' && str[i])
		i++;
	while (str[i])
	{
		t[1]++;
		i++;
	}
	return (t);
}

char	**ft_split_env(char *str, char c)
{
	char	**t;
	int		*size;
	int		i;
	int		k;

	t = (char **)malloc(2 * sizeof(char));
	if (!t)
		ft_perror("malloc");
	size = count_words(str, c);
	t[0] = (char *)malloc((size[0] + 1) * sizeof(char));
	t[1] = (char *)malloc((size[1] + 1) * sizeof(char));
	if (!t[0] || !t[1])
		ft_perror("malloc");
	i = 0;
	k = 0;
	while (str[i] && str[i] != c)
		t[0][k++] = str[i++];
	if (str[i] && str[i] == c)
		i++;
	t[0][k] = '\0';
	k = 0;
	while (str[i])
		t[1][k++] = str[i++];
	t[1][k] = '\0';
	return (t);
}
