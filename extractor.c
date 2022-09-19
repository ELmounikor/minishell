/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor`.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/19 21:10:53 by mounikor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_starter(char **envi, int i)
{
	t_list	*env;

	i = 0;
	env = NULL;
	while (envi && envi[i])
		ft_lstadd_back(&env, ft_lstnew(ft_strdup(envi[i++]), 0));
	return (env);
}

t_env	*env_extractor(t_list *envi, t_list *input)
{
	t_env	env;
	int		i;

	env.cmd_count = cmd_count(input);
	env.env = (char **) malloc ((ft_lstsize(envi) + 1) * sizeof(char *));
	if (!env.env)
		return (0);
	i = 0;
	while (envi)
	{
		env.env[i++] = ft_strdup(envi->content);
		envi = envi->next;
	}
	env.env[i] = NULL;
	env.paths = get_paths(env.env);
	return (&env);
}

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
		free(abs_path);
	}
	return (NULL);
}

void	cmd_filler(t_cmd *cmd, t_list **input, int size)
{
	int	i;

	i = 0;
	cmd->args = (char **) malloc (++size * sizeof(char *));
	cmd->file_des[0] = 0;
	cmd->file_des[1] = 0;
	cmd->limiter = NULL;
	while (*(input) && *(input)->id != 1)
	{
		if (*(input)->id % 4 && *(input)->id % 7 && *(input)->id % 77)
			cmd->args[i++] = ft_strdup(*(input)->content);
		else
			file_handler(*(input), &(cmd->file_des[0]), &(cmd->file_des[1]), \
			&(cmd->limiter));
		*(input) = *(input)->next;
	}
	cmd->args[i] = NULL;
	cmd->path = get_path(cmd->args[0]);
}

t_cmd	**cmd_extractor(t_list *input)
{
	t_cmd	*cmd;
	int		*sizes;
	int		i;

	cmd = (t_cmd *) malloc (cmd_count(input) * sizeof (t_cmd));
	if (!cmd)
		return (0);
	sizes = cmd_size(input);
	i = 0;
	while (input)
	{
		cmd_filler(&cmd[i], &input, sizes[i]);
		i++;
		if (input)
			input = input->next;
	}
	free(sizes);
	return (&cmd);
}

void	free_cmds(t_cmd **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		free(cmds[i]->path);
		ft_split_cleaner(cmds[i]->args);
		free(cmds[i]);
	}
	free(cmds);
}
