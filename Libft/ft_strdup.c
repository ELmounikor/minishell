/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 21:15:25 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/14 18:42:36 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;

	if (!s1)
		return (0);
	i = 0;
	while (s1[i])
		i++;
	s2 = (char *) malloc((i + 1) * sizeof(char));
	if (!s2)
		return (0);
	s2[i] = '\0';
	while (--i >= 0)
		s2[i] = s1[i];
	return (s2);
}
