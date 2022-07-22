/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:53:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/07/22 20:07:17 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*s;

	while (1)
	{
		s = write_history();
		if (ft_strncmp(s, "exit\n", 7) == 0)
		{
			printf("%s", s);
			ft_free(&s);
			break ;
		}
		else if (ft_strncmp(s, "history\n", 10) == 0)
			get_history(s, 5);
		else
		{
			printf("%s", s);
			ft_free(&s);
		}
	}
}
