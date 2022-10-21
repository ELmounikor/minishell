/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/21 16:39:25 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *file_name, char code, int fd)
{
	int	file;

	if (code == 'I')
	{
		fd = open(file_name, O_RDONLY);
		if (fd < 0)
		{
			g_exit_value = 1;
			perror(file_name);
		}
		return (fd);
	}
	else if (code == 'A')
		file = open(file_name, O_WRONLY | O_APPEND);
	else
		file = open(file_name, O_WRONLY | O_TRUNC);
	if (file == -1)
		file = open(file_name, O_WRONLY | O_CREAT, 0666);
	if (file == -1)
	{
		g_exit_value = 1;
		perror(file_name);
	}
	return (file);
}

void	in_file_handler(t_list *token, int *fd_in)
{
	char		*s;

	s = NULL;
	if (*fd_in > 0)
		close(*fd_in);
	if (token->id == -4 || token->id == -40)
	{
		g_exit_value = 1;
		ft_putstr_fd("sh-sm: ", 2);
		ft_putstr_fd(token->content, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		*fd_in = -2;
	}
	else
		*fd_in = open_file(token->content, 'I', *fd_in);
}

void	out_file_handler(t_list *token, int *fd_out)
{
	if (*fd_out > 0)
		close(*fd_out);
	if (token->id == -7 || token->id == -77 || \
	token->id == -70 || token->id == -770)
	{
		g_exit_value = 1;
		ft_putstr_fd("sh-sm: ", 2);
		ft_putstr_fd(token->content, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		*fd_out = -2;
	}
	else if (token->id % 77 == 0 && fd_out >= 0)
		*fd_out = open_file(token->content, 'A', *fd_out);
	else if (token->id % 7 == 0 && fd_out >= 0)
		*fd_out = open_file(token->content, 'T', *fd_out);
}

int	file_handler(t_cmd **cmd, t_list *token)
{
	if (!is_file(token->id))
		return (0);
	if ((*cmd)->fd[1] < 0 || (*cmd)->fd[0] < 0)
		return (1);
	else if (token->id % 7 == 0)
		out_file_handler(token, &((*cmd)->fd[1]));
	else if (token->id % 4 == 0)
		in_file_handler(token, &((*cmd)->fd[0]));
	return (1);
}
