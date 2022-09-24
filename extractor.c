/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/23 16:58:51 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_starter(char **envi, int i)
{
	t_list	*env_i;

	i = 0;
	env_i = NULL;
	while (envi && envi[i])
		ft_lstadd_back(&env_i, ft_lstnew(ft_strdup(envi[i++]), 0));
	return (env_i);
}

/*
char	**get_paths(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	path = env[i];
	if (!path)
		return (NULL);
	return (ft_split(path + 5, ':'));
}
t_env	*env_extractor(t_list *env_i, t_list *input)
{
	int		i;
	t_list	*tmp;
	t_env	env;

	if (input)
		env.cmd_count = cmd_count(input);
	if (env_i)
		env.env_i = env_i;
	env.env = (char **) malloc ((ft_lstsize(env.env_i) + 1) * sizeof(char *));
	if (!env.env)
		return (0);
	i = 0;
	tmp = env.env_i;
	while (tmp)
	{
		env.env[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	env.env[i] = NULL;
	env.paths = get_paths(env.env);
	return (env);
}

char	*get_path(char *cmd, char **paths)
{
	char	*abs_path;
	int		i;

	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (ft_strdup(cmd));
	i = -1;
	while (paths[++i])
	{
		abs_path = ft_strjoin_slash(paths[i], cmd);
		if (!access(abs_path, X_OK))
			return (abs_path);
		ft_free(&abs_path);
	}
	return (NULL);
}
*/
void	cmd_filler(t_cmd *cmd, t_list **input, int size)
{
	int	i;

	cmd->args = (char **) malloc (size * sizeof(char *));
	cmd->file_des[0] = 0;
	cmd->file_des[1] = 0;
	cmd->limiter = NULL;
	while ((*input) && (*input)->id != 1)
	{
		i = 0;
		if (!(*input)->id || ((*input)->id % 4 && (*input)->id % 7 && \
		(*input)->id % 77))
			cmd->args[i++] = ft_strdup((*input)->content);
		else
			file_handler((*input), &(cmd->file_des[0]), &(cmd->file_des[1]), \
			&(cmd->limiter));
		(*input) = (*input)->next;
	}
	cmd->args[i] = NULL;
	cmd->path = NULL;
}

t_cmd	**cmd_extractor(t_list *input)
{
	t_cmd	**cmd;
	int		*sizes;
	int		i;

	sizes = cmd_size(input);
	cmd = (t_cmd **) malloc (cmd_count(input) * sizeof (t_cmd *));
	if (!cmd)
		return (0);
	sizes = cmd_size(input);

	i = 0;
	while (input)
	{
		cmd_filler(cmd[i], &input, sizes[i] + 1);
		i++;
		if (input)
			input = input->next;
	}
	free(sizes);
	return (cmd);
}

void	free_cmds(t_cmd **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		ft_free(&cmds[i]->path);
		ft_split_cleaner(cmds[i]->args);
		free(cmds[i]);
	}
	free(cmds);
}
