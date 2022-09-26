/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:46:07 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/18 14:44:59 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	len_str;

	if (!s)
		return (0);
	len_str = ft_strlen(s);
	if (start > len_str)
		start = len_str;
	if (len + start >= len_str)
		len = len_str - start;
	new_str = (char *) malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (0);
	i = 0;
	if (len_str > start)
	{
		while (i < len && s[start])
			new_str[i++] = s[start++];
	}
	new_str[i] = 0;
	return (new_str);
}
