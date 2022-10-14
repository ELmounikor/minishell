/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/14 16:00:09 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_file_handler(t_list *token, int *fd_in, int cmd_id, t_env *env)
{
	char	*s;

	s = NULL;
	if (token->id % 44 == 0)
	{
		*fd_in = here_doc(token, cmd_id, &s, env);
		ft_free(&s);
	}
	else if (token->id % 4 == 0)
		*fd_in = handle_file(token->content, 'I', *fd_in);
}

void	out_file_handler(t_list *token, int *fd_out)
{
	if (token->id % 77 == 0 && fd_out >= 0)
		*fd_out = handle_file(token->content, 'A', *fd_out);
	else if (token->id % 7 == 0 && fd_out >= 0)
		*fd_out = handle_file(token->content, 'T', *fd_out);
}

int	file_handler(t_cmd **cmd, t_list *token, int cmd_id, t_env *env)
{
	if (token->id % 7 == 0)
		out_file_handler(token, &(*cmd)->fd[1]);
	else if (token->id % 4 == 0)
		in_file_handler(token, &(*cmd)->fd[0], cmd_id, env);
	if (token->id % 44 == 0 && g_exit_value)
		return (1);
	return (0);
}

void	cmd_filler(t_cmd **cmd, t_list **input, int cmd_id, t_env *env)
{
	int			i;

	i = 0;
	if (!(*cmd))
		return ;
	(*cmd)->args = (char **) malloc ((*cmd)->size * sizeof(char *));
	(*cmd)->fd[0] = 0;
	(*cmd)->fd[1] = 0;
	while ((*input) && (*input)->id != 1 && (*cmd)->args)
	{
		if ((*input)->id != 7 && (*input)->id != 77 && (*input)->id != 4 && \
		(*input)->id != 44 && (*input)->id != 70 && (*input)->id != 770 && \
		(*input)->id != 40 && (*input)->id != 440 && (*input)->id != 88 && \
		(*input)->id != 880)
			(*cmd)->args[i++] = ft_strdup((*input)->content);
		else if (file_handler(cmd, (*input), cmd_id, env))
		{
			(*cmd)->args[i] = NULL;
			ft_split_cleaner((*cmd)->args);
			free(*cmd);
			*cmd = NULL;
			break ;
		}
		(*input) = (*input)->next;
	}
	if (*cmd && (*cmd)->args)
		(*cmd)->args[i] = NULL;
}

t_cmd	**cmd_extractor(t_list *input, t_env *env)
{
	t_cmd	**cmd;
	int		*sizes;
	int		i;

	cmd = (t_cmd **) malloc ((cmd_count(input) + 1) * sizeof (t_cmd *));
	sizes = cmd_size(input);
	i = -1;
	while (cmd && input && ++i)
	{
		cmd[i] = (t_cmd *) malloc (sizeof(t_cmd));
		if (cmd[i])
			cmd[i]->size = sizes[i] + 1;
		cmd_filler(&cmd[i], &input, i, env);
		if (!cmd[i] || !input)
			break ;
		input = input->next;
	}
	if (!cmd || !cmd[i])
	{
		free_cmds(cmd);
		return (0);
	}
	cmd[i] = NULL;
	free(sizes);
	return (cmd);
}
