/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:30:46 by mel-kora          #+#    #+#             */
/*   Updated: 2022/06/14 22:01:27 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	while (s && s[length])
	{
		length++;
	}
	return (length);
}
