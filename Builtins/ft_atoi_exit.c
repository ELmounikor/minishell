/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:47:34 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/21 17:38:27 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_value(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, str, ft_strlen(tmp->variable) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_swap(t_env *tmp1, t_env *tmp2)
{
	char	*var;
	char	*val;

	var = tmp1->variable;
	val = tmp1->value;
	tmp1->variable = tmp2->variable;
	tmp1->value = tmp2->value;
	tmp2->variable = var;
	tmp2->value = val;
}

void	ft_sort_list(t_env **l)
{
	t_env	*tmp1;
	t_env	*tmp2;
	int		r;

	tmp1 = *l;
	while (tmp1->next)
	{
		tmp2 = tmp1;
		while (tmp2)
		{
			r = ft_strcmp(tmp1->variable, tmp2->variable);
			if ((r > 0) || (r == 0 && ft_strcmp(tmp1->value, tmp2->value) > 0))
				ft_swap(tmp1, tmp2);
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

int	get_number(const char	*str, int signe, int *err)
{
	unsigned long long int	nbr;

	nbr = 0;
	*err = 0;
	while (*str >= '0' && *str <= '9' )
	{
		nbr = nbr * 10 + (*str - '0');
		if (signe == 1 && nbr > 9223372036854775807)
		{
			*err = 1;
			return (-1);
		}
		else if (signe == -1 && (nbr - 1) > 9223372036854775807)
		{
			*err = 1;
			return (0);
		}
		str++;
	}
	return ((int)(nbr * signe));
}

int	ft_atoi_exit(const char *str, int *err)
{
	unsigned long	nbr;
	int				signe;

	signe = 1;
	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' )
	{
		signe = signe * -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (get_number(str, signe, err));
}
