/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:14:44 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/18 14:44:17 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * (size + 1));
	if (!s3)
		return (0);
	i = 0;
	j = 0;
	while (j < ft_strlen(s1))
		s3[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen(s2))
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}
