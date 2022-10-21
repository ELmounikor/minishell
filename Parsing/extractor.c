/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/21 17:01:18 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checkout_heredoc(t_cmd ***cmd, t_list **input, char **s)
{
	ft_free(&((*input)->content));
	(*input)->content = ft_strdup(*s);
	ft_free(s);
	if (g_exit_value)
	{
		if (*cmd)
		{
			free(*cmd);
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

	*cmd = (t_cmd **) malloc ((cmd_count(input) + 1) * sizeof (t_cmd *));
	*sizes = cmd_size(input);
	cmd_id = 0;
	while (input)
	{
		while (input && input->id != 1)
		{
			if (is_file(input->id) && !(input->id % 44))
			{
				here_doc(input, cmd_id, &s, env);
				if (!checkout_heredoc(cmd, &input, &s))
					break ;
			}
			input = input->next;
		}
		cmd_id++;
		if (!input || (input && is_file(input->id) && \
		!(input->id % 44) && g_exit_value))
			break ;
		input = input->next;
	}
	return (*cmd);
}

void	cmd_filler(t_cmd **cmd, t_list **input)
{
	int	i;

	i = 0;
	if (!(*cmd))
		return ;
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
		if (cmd[i])
			cmd[i]->size = sizes[i] + 1;
		cmd_filler(&cmd[i], &input);
		if (!input)
			break ;
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
