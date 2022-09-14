/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 21:02:44 by mel-kora          #+#    #+#             */
/*   Updated: 2022/08/21 16:09:40 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	lenght;

	if (!lst)
		return (0);
	lenght = 0;
	while (lst)
	{
		lst = lst->next;
		lenght++;
	}
	return (lenght);
}
