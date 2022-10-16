/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:13:50 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/16 10:37:33 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/ft_pipe.h"

void	handler_sig(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_value = 1;
	}
	else if (signum == SIGQUIT)
	{
		g_exit_value = 0;
		//printf("dga\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handler_child(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("^\\Quit: 3\n");
		g_exit_value = 131;
	}
}