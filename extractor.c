/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/29 16:22:16 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	param_extractor(t_params	**params, t_env *env, t_list *input)
{
	int		i;

	if (input)
	{
		(*params)->cmd_count = cmd_count(input);
		(*params)->last_exit_code = 0;
	}
	if (env)
		(*params)->env = env;
	ft_split_cleaner((*params)->en);
	(*params)->en = (char **) malloc ((ft_envsize((*params)->env) + 1) * \
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
	(*params)->paths = NULL;
}

void	cmd_filler(t_cmd **cmd, t_list **input, int size, int cmd_id, t_env *env)
{
	int	i;

	(*cmd) = (t_cmd *) malloc (sizeof(t_cmd));
	if (!(*cmd))
		return ;
	(*cmd)->args = (char **) malloc (size * sizeof(char *));
	(*cmd)->fd[0] = 0;
	(*cmd)->fd[1] = 0;
	i = 0;
	while ((*input) && (*input)->id != 1 && (*cmd)->args)
	{
		if ((*input)->id != 7 && (*input)->id != 77 && (*input)->id != 4 && \
		(*input)->id != 44 && (*input)->id != 70 && (*input)->id != 770 && \
		(*input)->id != 40 && (*input)->id != 440 && (*input)->id != 88 && \
		(*input)->id != 880 && (*input)->content)
			(*cmd)->args[i++] = ft_strdup((*input)->content);
		else if ((*input)->id == 7 || (*input)->id == 77 || (*input)->id == 4 \
		|| (*input)->id == 44 || (*input)->id == 70 || (*input)->id == 770 || \
		(*input)->id == 40 || (*input)->id == 440 || (*input)->id == 88 || \
		(*input)->id == 880)
			file_handler((*input), &((*cmd)->fd[0]), &((*cmd)->fd[1]), cmd_id, env);
		(*input) = (*input)->next;
	}
	if ((*cmd)->args)
		(*cmd)->args[i] = NULL;
}

t_cmd	**cmd_extractor(t_list *input, t_env *env)
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
		cmd_filler(&cmd[i], &input, sizes[i] + 1, i, env);
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

	if (!cmd)
		return ;
	i = -1;
	while (cmd[++i])
	{
		// ft_free(&(cmd[i]->path));
		ft_split_cleaner(cmd[i]->args);
		if (cmd[i]->fd[0] > 0)
			close(cmd[i]->fd[0]);
		if (cmd[i]->fd[1] > 0)
			close(cmd[i]->fd[1]);
		free(cmd[i]);
	}
	free(cmd);
}
