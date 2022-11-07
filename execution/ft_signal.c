/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:13:50 by sennaama          #+#    #+#             */
/*   Updated: 2022/11/07 17:09:03 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipe.h"

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
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_exit_value = 130;
	}
	if (sig == SIGQUIT)
	{
		printf("^\\Quit: 3\n");
		g_exit_value = 131;
	}
}

void	handler_fake(int sig)
{
	if (sig)
		return ;
}
