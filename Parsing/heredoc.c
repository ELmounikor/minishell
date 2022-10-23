/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:40:30 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/23 19:11:16 by mel-kora         ###   ########.fr       */
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

char	*get_val(char *s1, t_env *env)
{
	if (!ft_strcmp(s1, "?"))
	{
		ft_free(&s1);
		return (ft_itoa(g_exit_value));
	}
	else if (!ft_strcmp(s1, "0"))
	{
		ft_free(&s1);
		return (ft_strdup("sh-sm"));
	}
	while (env && s1)
	{
		if (!ft_strcmp(s1, env->variable))
			return (ft_strdup(env->value));
		env = env->next;
	}
	ft_free(&s1);
	return (0);
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
				editor(&s, get_val(ft_substr((*line), j, i - j), env));
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
		rl_on_new_line();
	}
}

void	here_doc(t_list *token, int cmd_id, char **file_name, t_env *env)
{
	int			fd;
	int			stdin_fd;
	char		*s;

	g_exit_value = 0;
	stdin_fd = dup(STDIN_FILENO);
	*file_name = get_file_name(cmd_id);
	fd = open(*file_name, O_RDWR | O_TRUNC | O_CREAT, 0666);
	signal(SIGINT, handler_heredoc);
	s = readline("> ");
	while (s && ft_strcmp(s, token->content) && !g_exit_value)
	{
		s = line_expander(&s, env, 0, token->id);
		ft_putstr_fd(s, fd);
		ft_putstr_fd("\n", fd);
		ft_free(&s);
		s = readline("> ");
	}
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
	close(fd);
	ft_free(&s);
}