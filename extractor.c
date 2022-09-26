/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/26 19:20:51 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	param_extractor(t_params	**params, t_env *env, t_list *input)
{
	int		i;

	if (input)
	{
		*params = (t_params *) malloc (sizeof(t_params));
		(*params)->cmd_count = cmd_count(input);
		(*params)->last_exit_code = 0;
	}
	if (env)
		(*params)->env = env;
	ft_split_cleaner((*params)->en);
	(*params)->en = (char **) malloc ((ft_lstsize((*params)->env) + 1) * \
	sizeof(char *));
	if (!(*params)->en)
		return ;
	i = 0;
	while ((*params)->env)
	{
		(*params)->en[i++] = ft_strjoin_char((*params)->env->variable, \
		(*params)->env->value, '=');
		(*params)->env = (*params)->env->next;
	}
	(*params)->en[i] = NULL;
	ft_split_cleaner((*params)->paths);
	(*params)->paths = get_paths((*params)->env);
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
