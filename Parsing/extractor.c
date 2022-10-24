/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/24 18:05:20 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_file(t_list *token)
{
	if (token->id != 7 && token->id != 77 && token->id != 4 && \
	token->id != 44 && token->id != 70 && token->id != 770 && \
	token->id != 40 && token->id != 440 && token->id != 88 && \
	token->id != 880 && token->id != -7 && token->id != -77 && \
	token->id != -4 && token->id != -70 && token->id != -770 && \
	token->id != -40)
		return (0);
	return (1);
}

int	checkout_heredoc(t_cmd ***cmd, int **sizes, t_list **input, char **s)
{
	ft_free(&((*input)->content));
	(*input)->content = ft_strdup(*s);
	ft_free(s);
	if (g_exit_value)
	{
		if (*cmd)
		{
			free(*cmd);
			free(*sizes);
			*cmd = NULL;
			return (0);
		}
	}
	return (1);
}

void	*open_heredoc(t_list *input, t_env *env, t_cmd ***cmd, int **sizes)
{
	char	*s;
	int		cmd_id;

	if (!input)
		return (0);
	*cmd = (t_cmd **) malloc ((cmd_count(input) + 1) * sizeof (t_cmd *));
	*sizes = cmd_size(input);
	cmd_id = 0;
	while (input)
	{
		while (input && input->id != 1)
		{
			if (is_file(input) && !(input->id % 44))
			{
				here_doc(input, cmd_id, &s, env);
				if (!checkout_heredoc(cmd, sizes, &input, &s))
					return (0);
			}
			input = input->next;
		}
		cmd_id++;
		if (input)
			input = input->next;
	}
	return (*cmd);
}

void	cmd_filler(t_cmd **cmd, t_list **input, int cmd_size)
{
	int	i;

	i = 0;
	if (!(*cmd))
		ft_perror("cmd malloc");
	(*cmd)->size = cmd_size;
	(*cmd)->args = (char **) malloc ((*cmd)->size * sizeof(char *));
	(*cmd)->fd[0] = 0;
	(*cmd)->fd[1] = 0;
	while ((*input) && (*input)->id != 1 && (*cmd)->args)
	{
		if (!file_handler(cmd, (*input)) && (*input)->content)
			(*cmd)->args[i++] = ft_strdup((*input)->content);
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

	if (!open_heredoc(input, env, &cmd, &sizes))
		return (0);
	i = -1;
	while (cmd && input)
	{
		cmd[++i] = (t_cmd *) malloc (sizeof(t_cmd));
		cmd_filler(&cmd[i], &input, sizes[i] + 1);
		if (input)
			input = input->next;
	}
	free(sizes);
	cmd[++i] = NULL;
	if (!cmd)
	{
		free_cmds(cmd);
		return (0);
	}
	return (cmd);
}
