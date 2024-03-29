/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 21:02:44 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/23 19:03:47 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_list *lst)
{
	int	lenght;

	lenght = 0;
	while (lst)
	{
		lst = lst->next;
		lenght++;
	}
	return (lenght);
}

int	ft_envsize(t_env *lst)
{
	int	lenght;

	lenght = 0;
	while (lst)
	{
		lst = lst->next;
		lenght++;
	}
	return (lenght);
}

int	cmd_count(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		while (lst && lst->id != 1)
			lst = lst->next;
		count++;
		if (lst)
			lst = lst->next;
	}
	return (count);
}

int	*cmd_size(t_list *lst)
{
	int	*size;
	int	i;

	if (!cmd_count(lst))
		return (NULL);
	size = (int *) malloc(cmd_count(lst) * sizeof(int));
	if (!size)
		return (NULL);
	i = -1;
	while (lst)
	{
		size[++i] = 0;
		while (lst && lst->id != 1)
		{
			if (!is_file(lst) && lst->content)
				size[i]++;
			lst = lst->next;
		}
		if (lst)
			lst = lst->next;
	}
	return (size);
}
