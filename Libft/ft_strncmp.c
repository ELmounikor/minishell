/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:27:31 by mel-kora          #+#    #+#             */
/*   Updated: 2022/06/14 22:05:31 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int				i;
	unsigned char	*d1;
	unsigned char	*d2;

	i = 0;
	d1 = (unsigned char *) s1;
	d2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (n-- > 0 && (d1[i] || d2[i]))
	{
		if (d1[i] != d2[i])
		{
			return (d1[i] - d2[i]);
		}
		i++;
	}
	return (0);
}
