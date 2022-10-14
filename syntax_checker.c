/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:17:01 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/14 19:21:50 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(char *s)
{
	int	flag[3];

	flag[0] = -1;
	flag[1] = 0;
	flag[2] = 0;
	while (s && s[++flag[0]])
	{
		if (s[flag[0]] == 34 && flag[1] % 2 == 0)
			flag[2]++;
		else if (s[flag[0]] == 39 && flag[2] % 2 == 0)
			flag[1]++;
	}
	if (flag[2] % 2 == 0 && flag[1] % 2 == 0)
		return (1);
	else
		return (0);
}

t_list	*open_fake_heredoc(t_list *head, t_env *env)
{
	t_list	*tmp;
	char	*s;

	s = NULL;
	tmp = getter(&head, env);
	head = tmp;
	while (head && head->id != -1)
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

t_list	*throw_error(t_list *tokens, t_list *head, t_env *env)
{
	char	*s;
	t_list	*tmp;

	s = NULL;
	tokens->id = -1;
	if (tokens->content)
	{
		printf ("syntax error near unexpected token '%s'\n", tokens->content);
		tmp = open_fake_heredoc(head, env);
	}
	else if (tokens->next && tokens->next->content)
	{
		printf ("syntax error near unexpected token '%s'\n", \
		tokens->next->content);
		tmp = open_fake_heredoc(head, env);
	}
	else
	{
		tmp = open_fake_heredoc(head, env);
		printf ("syntax error near unexpected token `newline'\n");
	}
	return (tmp);
}

t_list	*check(t_list *previous, t_list *current, t_list *head, t_env *env)
{
	if (current && (current->id == 44 || current->id == 4 || \
	current->id == 440 || current->id == 40 || current->id == 770 || \
	current->id == 70 || current->id == 77 || current->id == 7) && \
	!(current->content || (current->next && (current->next->id != 44 && \
	current->next->id != 4 && current->next->id != 440 && current->next->id != \
	40 && current->next->id != 770 && current->next->id != 70 && \
	current->next->id != 77 && current->next->id != 7 && current->next->id != 1 \
	))))
		return (throw_error(current, head, env));
	else if (current && current->id == 1 && !(previous && current->next && \
	previous->id != 1 && !(current->next->id == 1 || (!current->next->id && \
	current->next->content && !current->next->content[0]))))
		return (throw_error(current, head, env));
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
