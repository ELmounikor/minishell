/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:31:41 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/24 14:36:43 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s3;
	unsigned char	*s4;

	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (s3[i] == s4[i] && s3[i] && s4[i] && i < n - 1)
		i++;
	if ((s3[i] - s4[i]) > 0)
		return (1);
	else if ((s3[i] - s4[i]) < 0)
		return (-1);
	return (0);
}
