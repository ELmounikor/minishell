/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:47:34 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/28 16:50:34 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_number(const char	*str, int signe, int *err)
{
	unsigned long	nbr;

	nbr = 0;
	*err = 0;
	while (*str >= '0' && *str <= '9' )
	{
		nbr = nbr * 10 + (*str - '0');
		if (signe == 1 && nbr >= 9223372036854775807)
		{
			*err = 1;
			return (-1);
		}
		else if (signe == -1 && nbr > 9223372036854775807)
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