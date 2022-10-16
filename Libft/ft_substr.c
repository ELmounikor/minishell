/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:41:31 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/14 19:53:12 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*output;
	unsigned int		i;
	unsigned int		slen;

	i = 0;
	if (!s)
		return (0);
	slen = (unsigned int) ft_strlen(s);
	if (start > slen)
		start = slen;
	if (start + len > slen)
		len = slen - start;
	if (len == 0)
		return (0);
	output = (char *) malloc (len + 1);
	if (!output)
		return (0);
	if (start < slen)
	{
		while (i < len && s[start])
			output[i++] = s[start++];
	}
	output[i] = '\0';
	return (output);
}
