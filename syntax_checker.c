/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:17:01 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/28 18:04:41 by mel-kora         ###   ########.fr       */
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

int	throw_error(t_list *tokens)
{
	if (tokens->content)
		printf ("syntax error near '%s'\n", tokens->content);
	else if (tokens->next && tokens->next->content)
		printf ("syntax error near unexpected token '%s'\n", \
		tokens->next->content);
	else
		printf ("syntax error near unexpected token `newline'\n");
	return (0);
}

int	check(t_list *previous, t_list *current, t_list *next)
{
	if (current && (current->id == 44 || current->id == 4 || \
	current->id == 440 || current->id == 40 || current->id == 770 || \
	current->id == 70 || current->id == 77 || current->id == 7) && \
	!(current->content || (next && (next->id != 44 && next->id != 4 && \
	next->id != 440 && next->id != 40 && next->id != 770 && next->id != 70 && \
	next->id != 77 && next->id != 7 && next->id != 1))))
		return (throw_error(current));
	else if (current && current->id == 1 && !(previous && next && \
	previous->id != 1 && next->id != 1))
		return (throw_error(current));
	return (1);
}

t_list	*syntax_checker(t_list **tokens, t_env *env)
{
	t_list	*previous;
	t_list	*current;

	current = *tokens;
	previous = NULL;
	while (current && check(previous, current, current->next))
	{
		previous = current;
		current = current->next;
	}
	if (current)
	{
		ft_lstclear(tokens, &free);
		return (0);
	}
	return (getter(tokens, env));
}
