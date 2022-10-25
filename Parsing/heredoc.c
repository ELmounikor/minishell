/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:40:30 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/25 18:08:49 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_file_name(int cmd_id)
{
	char		**dic;
	char		*file_name;
	static int	file_id;
	int			fd;

	if (cmd_id == 0)
		file_id = '0';
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
				editor(&s, getval(ft_substr((*line), j, i - j), env, NULL));
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
	{
		g_exit_value = 1;
		write(1, "\n", 1);
		close(0);
	}
}

void	write_in_heredoc(char *file_name, t_list *token, t_env *env)
{
	char	*s;
	int		fd;

	fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 0666);
	s = readline("> ");
	while (s && ft_strcmp(s, token->content) && !g_exit_value)
	{
		s = line_expander(&s, env, 0, token->id);
		ft_putstr_fd(s, fd);
		ft_putstr_fd("\n", fd);
		ft_free(&s);
		s = readline("> ");
	}
	ft_free(&s);
	close(fd);
}

void	heredoc(t_list *token, int cmd_id, char **file_name, t_env *env)
{
	int	stdin_fd;

	g_exit_value = 0;
	stdin_fd = dup(STDIN_FILENO);
	*file_name = get_file_name(cmd_id);
	signal(SIGINT, handler_heredoc);
	write_in_heredoc(*file_name, token, env);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
}
