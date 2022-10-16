/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:46:25 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/26 22:50:02 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (del && lst->content)
		del(lst->content);
	free(lst);
}

void	ft_envdelone(t_env *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (del && lst->variable)
		del(lst->variable);
	if (del && lst->value)
		del(lst->value);
	free(lst);
}
