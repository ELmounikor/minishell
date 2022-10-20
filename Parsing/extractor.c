/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/20 12:39:30 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	in_file_handler(t_list *token, int *fd_in, int cmd_id, t_env *env)
{
	char	*s;

	s = NULL;
	if (*fd_in > 0)
		close(*fd_in);
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
	if (*fd_out > 0)
		close(*fd_out);
	if (token->id % 77 == 0 && fd_out >= 0)
		*fd_out = handle_file(token->content, 'A', *fd_out);
	else if (token->id % 7 == 0 && fd_out >= 0)
		*fd_out = handle_file(token->content, 'T', *fd_out);
}

int	file_handler(t_cmd **cmd, t_list *token, int cmd_id, t_env *env)
{
	if (!is_file(token->id))
		return (0);
	if ((*cmd)->fd[1] < 0 || (*cmd)->fd[0] < 0)
		return (1);
	if (token->id == -7 || token->id == -77 || \
	token->id == -70 || token->id == -770)
	{
		(*cmd)->fd[1] = -2;
		ft_putstr_fd(token->content, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	else if (token->id == -4 || token->id == -40)
	{
		(*cmd)->fd[0] = -2;
		ft_putstr_fd(token->content, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	else if (token->id % 7 == 0)
		out_file_handler(token, &((*cmd)->fd[1]));
	else if (token->id % 4 == 0)
		in_file_handler(token, &((*cmd)->fd[0]), cmd_id, env);
	return (1);
}

void	cmd_filler(t_cmd **cmd, t_list **input, int cmd_id, t_env *env)
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
		if (file_handler(cmd, (*input), cmd_id, env))
		{
			if ((*input)->id % 44 == 0 && g_exit_value == 1)
				break ;
		}
		else if ((*input)->content)
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

	cmd = (t_cmd **) malloc ((cmd_count(input) + 1) * sizeof (t_cmd *));
	sizes = cmd_size(input);
	i = -1;
	while (cmd && input && i >= -1)
	{
		cmd[++i] = (t_cmd *) malloc (sizeof(t_cmd));
		if (cmd[i])
			cmd[i]->size = sizes[i] + 1;
		cmd_filler(&cmd[i], &input, i, env);
		if (!input || (input && input->id % 44 == 0 && g_exit_value == 1))
			break ;
		input = input->next;
	}
	free(sizes);
	cmd[++i] = NULL;
	if (!cmd || (input && input->id % 44 == 0 && g_exit_value == 1))
	{
		free_cmds(cmd);
		return (0);
	}
	return (cmd);
}
