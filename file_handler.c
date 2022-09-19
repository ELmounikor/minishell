/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/19 22:23:47 by mounikor         ###   ########.fr       */
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

int	here_doc(char	*limiter)
{
	int		fd;
	char	*s;

	fd = open("/tmp/.tmp.t", O_WRONLY | O_TRUNC | O_CREAT, 0666)
	s = readline("> ");
	while (s && ft_strncmp(s, limiter, ft_strlen(limiter) + 1))
	{
		ft_putstr_fd(s, fd);
		ft_free(&s);
		s = readline("> ");
	}
	ft_free(&limiter);
	close(fd);
	//problem kan khas chi random name generator bash kol here_doc yl9a file lih bohdo fin yktb l cmd input
	//solution nkhli lik code fl in_file matalan -444 ola l9itih 3yti l heredoc b limiter li an3tik :3
	return (open("/tmp/.tmp.t", O_RDWR));
}

int	handle_infile(char *file_name, int fd)
{
	int	in;

	if (fd > 0)
		close(fd);
	in = open(file_name, O_RDONLY);
	if (in < 0)
		perror(file_name);
	if (in == -1)
		in = open("/tmp/.tmp_reader.t", O_RDONLY | O_TRUNC | O_CREAT, 0666);
	return (in);
}

void    file_handler(t_list *token, int *fd_in, int *fd_out, char **limiter)
{
	if (token->id % 77 && out >= 0)
		*fd_out = handle_outfile(token->content, 'A', fd_out);
	else if (token->id % 7 && out >= 0)
		*fd_out = handle_outfile(token->content, 'T', fd_out);
	else if (token->id % 44)
	{
		if (*fd_in > 0)
			close(*fd_in);
		*fd_in = -444;//code sent with <3
		ft_free(limiter);
		*limiter = ft_strjoin(token->content, "\n");
	}
	else if (token->id % 4)
		*fd_in = handle_infile(token->content, fd_in);
}
