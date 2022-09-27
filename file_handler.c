/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/27 19:10:20 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_outfile(char *file_name, char code, int fd)
{
	int	out;

	if (fd > 0)
		close(fd);
	if (code == 'A')
		out = open(file_name, O_RDWR | O_APPEND);
	else
		out = open(file_name, O_RDWR | O_TRUNC);
	if (out == -1)
		out = open(file_name, O_RDWR | O_CREAT, 0666);
	if (out == -1)
		perror(file_name);
	return (out);
}

int	here_doc(char	*limiter, int cmd_id, char **file_name)
{
	int			fd;
	char		*s;
	static int	i;

	i = -1;
	s = ttyname(0);
	fd = 0;
	while (fd <= 0)
	{
		ft_free(file_name);
		*file_name = ft_strjoin_char("/tmp/.", s, i + cmd_id);
		fd = open(*file_name, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	}
	ft_free(&s);
	s = readline("> ");
	while (s && ft_strncmp(s, limiter, ft_strlen(limiter) + 1))
	{
		ft_putstr_fd(s, fd);
		ft_free(&s);
		s = readline("> ");
	}
	ft_free(&limiter);
	close(fd);
	return (open(*file_name, O_RDWR));
}

int	handle_infile(char *file_name)
{
	int	in;

	in = open(file_name, O_RDONLY);
	if (in < 0)
		perror(file_name);
	// if (in == -1)
	// 	in = open("/tmp/.tmp_reader.t", O_RDONLY | O_TRUNC | O_CREAT, 0666);
	return (in);
}

void	file_handler(t_list *token, int *fd_in, int *fd_out, int cmd_id)
{
	char	*s;

	s = NULL;
	if (*fd_in > 0 && token->id % 4 == 0)
		close(*fd_in);
	if (token->id % 77 == 0 && fd_out >= 0)
		*fd_out = handle_outfile(token->content, 'A', *fd_out);
	else if (token->id % 7 == 0 && fd_out >= 0)
		*fd_out = handle_outfile(token->content, 'T', *fd_out);
	else if (token->id % 44 == 0)
	{
		*fd_in = here_doc(ft_strjoin(token->content, "\n"), cmd_id, &s);
		ft_free(&s);
	}
	else if (token->id % 4 == 0)
		*fd_in = handle_infile(token->content);
}
