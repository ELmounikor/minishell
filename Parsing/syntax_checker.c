/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:17:01 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/20 18:00:10 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*open_heredoc(t_list *head, t_env *env, int outfd)
{
	t_list	*tmp;
	char	*s;

	s = NULL;
	dup2(outfd, 1);
	if (head && head->id >= 0)
		head = getter(&head, env);
	tmp = head;
	while (head && head->id >= 0)
	{
		if (head->id && head->id % 44 == 0)
		{
			close(here_doc(head, 0, &s, env));
			ft_free(&s);
			if (g_exit_value)
				break ;
		}
		head = head->next;
	}
	return (tmp);
}

int	print_redirection(t_list *tokens, t_list **tmp, t_list *head, t_env *env)
{
	if (!tokens->next || !(tokens->next && \
	!(tokens->next->id % 7 && tokens->next->id % 4)))
		return (0);
	printf("sh-sm: syntax error near unexpected token '");
	if (tokens->next->id % 77 == 0)
		printf(">>'\n");
	else if (tokens->next->id % 7 == 0)
		printf(">'\n");
	else if (tokens->next->id % 44 == 0)
		printf("<<'\n");
	else if (tokens->next->id % 4 == 0)
		printf("<'\n");
	*tmp = open_heredoc(head, env, (tokens->id) * -1);
	return (1);
}

t_list	*throw_error(t_list *tokens, t_list *head, t_env *env, int outfd)
{
	t_list	*tmp;

	tokens->id = -outfd;
	if (tokens->content)
	{
		printf("sh-sm: syntax error near unexpected token '%s'\n", \
		tokens->content);
		tmp = open_heredoc(head, env, outfd);
	}
	else if (tokens->next && tokens->next->content)
	{
		printf("sh-sm: syntax error near unexpected token '%s'\n", \
		tokens->next->content);
		tmp = open_heredoc(head, env, outfd);
	}
	else if (!print_redirection(tokens, &tmp, head, env))
	{
		tmp = open_heredoc(head, env, outfd);
		dup2(2, 1);
		printf("sh-sm: syntax error near unexpected token `newline'\n");
	}
	dup2(outfd, 1);
	close(outfd);
	return (tmp);
}

t_list	*check(t_list *previous, t_list *current, t_list *head, t_env *env)
{
	int	outfd;

	outfd = dup(1);
	dup2(2, 1);
	if (current && (current->id == 44 || current->id == 4 || \
	current->id == 440 || current->id == 40 || current->id == 770 || \
	current->id == 70 || current->id == 77 || current->id == 7) && \
	!(current->content || (current->next && (current->next->id != 44 && \
	current->next->id != 4 && current->next->id != 440 && current->next->id != \
	40 && current->next->id != 770 && current->next->id != 70 && \
	current->next->id != 77 && current->next->id != 7 && current->next->id != 1 \
	))))
		return (throw_error(current, head, env, outfd));
	else if (current && current->id == 1 && !(previous && current->next && \
	previous->id != 1 && !(current->next->id == 1 || (!current->next->id && \
	current->next->content && !current->next->content[0]))))
		return (throw_error(current, head, env, outfd));
	dup2(outfd, 1);
	close(outfd);
	return (0);
}

t_list	*syntax_checker(t_list **tokens, t_env *env)
{
	t_list	*previous;
	t_list	*current;
	t_list	*head;
	t_list	*tmp;

	current = *tokens;
	previous = NULL;
	head = *tokens;
	tmp = NULL;
	while (current && !tmp)
	{
		tmp = check(previous, current, head, env);
		if (tmp)
			break ;
		previous = current;
		current = current->next;
	}
	if (tmp)
	{
		ft_lstclear(&tmp, &free);
		g_exit_value = 258;
		return (0);
	}
	return (getter(tokens, env));
}
