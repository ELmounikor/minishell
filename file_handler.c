/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/11 18:48:18 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_file(char *file_name, char code, int fd)
{
	int	file;

	if (fd > 0)
		close(fd);
	if (code == 'I')
	{
		fd = open(file_name, O_RDONLY);
		if (fd < 0)
			perror(file_name);
		return (fd);
	}
	else if (code == 'A')
		file = open(file_name, O_RDWR | O_APPEND);
	else
		file = open(file_name, O_RDWR | O_TRUNC);
	if (file == -1)
		file = open(file_name, O_RDWR | O_CREAT, 0666);
	if (file == -1)
		perror(file_name);
	return (file);
}

char	*get_file_name(int cmd_id, int file_id)
{
	char	**dic;
	char	*file_name;
	int		fd;

	dic = ft_split(ttyname(0), '/');
	file_name = ft_strjoin("/tmp/.", dic[1]);
	fd = 0;
	while (fd <= 0)
	{
		editor(&file_name, ft_strjoin_char("tmp", ".t", file_id + cmd_id));
		fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
		{
			file_id++;
			ft_free(&file_name);
			file_name = ft_strjoin("/tmp/.", dic[1]);
		}
	}
	ft_split_cleaner(dic);
	close(fd);
	return (file_name);
}

char	*line_expander(char **line, t_env *env, int i, int j)
{
	char	*s;

	s = NULL;
	if (j != 88 && j != 880)
	{
		while (*line && (*line)[i])
		{
			j = i;
			while ((*line)[i] && !((*line)[i] == '$' && (\
			ft_isalnum_((*line)[i + 1]) || (*line)[i + 1] == '?')))
				i++;
			editor(&s, ft_substr(*line, j, i - j));
			if ((*line)[i] == '$')
			{
				j = ++i;
				while ((ft_isalnum_((*line)[i]) && (*line)[j] != '?') || \
				(i == j && (*line)[j] == '?'))
					i++;
				editor(&s, getval(ft_substr((*line), j, i - j), env));
			}
		}
		ft_free(line);
		return (s);
	}
	return (*line);
}

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
		exit (1);
	else if (sig == SIGQUIT)
	{
		printf("--");
		//rl_redisplay();
	}
}

int	here_doc(t_list *token, int cmd_id, char **file_name, t_env *env)
{
	int			fd;
	int			pid;
	char		*s;
	static int	file_id;
	int			status;

	if (cmd_id == 0)
		file_id = 0;
	*file_name = get_file_name(cmd_id, file_id);
	fd = open(*file_name, O_RDWR | O_TRUNC | O_CREAT, 0666);
	pid = fork();
	if (pid == 0)
	{
		s = readline("> ");
		while (s && ft_strcmp(s, token->content))
		{
			signal(SIGINT, handler_heredoc);
			s = line_expander(&s, env, 0, token->id);
			ft_putstr_fd(s, fd);
			ft_putstr_fd("\n", fd);
			ft_free(&s);
			s = readline("> ");
			//signal(SIGQUIT, handler_heredoc);
		}
		exit (0);
	}
	if (waitpid(pid, &status, 0) != -1)
			g_exit_value = WEXITSTATUS(status);
	close(fd);
	return (open(*file_name, O_RDWR));
}

void	file_handler(t_list *token, int *fd_in, int *fd_out, int cmd_id, t_env *env)
{
	char	*s;

	s = NULL;
	if (token->id % 77 == 0 && fd_out >= 0)
		*fd_out = handle_file(token->content, 'A', *fd_out);
	else if (token->id % 7 == 0 && fd_out >= 0)
		*fd_out = handle_file(token->content, 'T', *fd_out);
	else if (token->id % 44 == 0)
	{
		*fd_in = here_doc(token, cmd_id, &s, env);
		ft_free(&s);
	}
	else if (token->id % 4 == 0)
		*fd_in = handle_file(token->content, 'I', *fd_in);
}
