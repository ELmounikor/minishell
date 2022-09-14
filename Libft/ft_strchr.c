/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:20:32 by mel-kora          #+#    #+#             */
/*   Updated: 2021/11/21 21:46:11 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (!c)
		return ((char *)s + i);
	return (0);
}
/*
#include <string.h>
#include <stdio.h> 
int	main(void)
{
	char *s = "mounia el koraichi";

	printf("%s\n", strchr(s, 0));
	printf("%d",  strchr(s, 0) == ft_strchr(s, 0));
}*/
