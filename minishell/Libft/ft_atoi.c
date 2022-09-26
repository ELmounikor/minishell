/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:20:01 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/24 16:22:34 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long int	ft_atoi(const char *str)
{
	unsigned long long int	n;
	long long int			i;
	int						sign;

	n = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - 48;
		if (sign == -1 && n > 9223372036854775807)
			return (-2);
		if (sign == 1 && n > 9223372036854775807)
			return (-2);
		i++;
	}
	return ((long long int) n * sign);
}
