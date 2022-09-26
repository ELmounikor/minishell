/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/26 15:25:02 by mel-kora         ###   ########.fr       */
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

void	env_extractor(t_env	**env, t_list *env_i, t_list *input)
{
	int		i;
	t_list	*tmp;

	if (input)
		(*env)->cmd_count = cmd_count(input);
	if (env_i)
		(*env)->env_i = env_i;
	ft_split_cleaner((*env)->env);
	(*env)->env = (char **) malloc ((ft_lstsize((*env)->env_i) + 1) * \
	sizeof(char *));
	if (!(*env)->env)
		return ;
	i = 0;
	tmp = (*env)->env_i;
	while (tmp)
	{
		(*env)->env[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	(*env)->env[i] = NULL;
	ft_split_cleaner((*env)->paths);
	(*env)->paths = get_paths((*env)->env);
}

void	cmd_filler(t_cmd **cmd, t_list **input, int size)
{
	int	i;

	(*cmd) = (t_cmd *) malloc (sizeof(t_cmd));
	if (!(*cmd))
		return ;
	(*cmd)->args = (char **) malloc (size * sizeof(char *));
	(*cmd)->file_des[0] = 0;
	(*cmd)->file_des[1] = 0;
	(*cmd)->limiter = NULL;
	(*cmd)->path = NULL;
	i = 0;
	while ((*input) && (*input)->id != 1)
	{
		if ((*input)->id != 7 && (*input)->id != 77 && (*input)->id != 4 && \
		(*input)->id != 44 && (*input)->id != 70 && (*input)->id != 770 && \
		(*input)->id != 40 && (*input)->id != 440 && (*cmd)->args)
			(*cmd)->args[i++] = ft_strdup((*input)->content);
		else
			file_handler((*input), &((*cmd)->file_des[0]), \
			&((*cmd)->file_des[1]), &((*cmd)->limiter));
		(*input) = (*input)->next;
	}
	if ((*cmd)->args)
		(*cmd)->args[i] = NULL;
}

t_cmd	**cmd_extractor(t_list *input)
{
	t_cmd	**cmd;
	int		*sizes;
	int		i;

	cmd = (t_cmd **) malloc ((cmd_count(input) + 1) * sizeof (t_cmd *));
	if (!cmd)
		return (0);
	sizes = cmd_size(input);
	i = 0;
	while (input)
	{
		cmd_filler(&cmd[i], &input, sizes[i] + 1);
		i++;
		if (input)
			input = input->next;
	}
	cmd[i] = NULL;
	free(sizes);
	return (cmd);
}

void	free_cmds(t_cmd **cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return ;
	while (cmd[++i])
	{
		ft_free(&cmd[i]->path);
		ft_split_cleaner(cmd[i]->args);
		free(cmd[i]);
	}
	free(cmd);
}
