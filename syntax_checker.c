/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:17:01 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/14 12:51:12 by mel-kora         ###   ########.fr       */
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
	current->id == 77 || current->id == 7) && !current->content)
		return (throw_error(current));
	else if (current && (current->id == 1 || current->id == 11 || \
	current->id == 22) && (!(previous && next) || !(previous->id != 11 && \
	previous->id != 1 && previous->id != 22 && next->id != 11 && next->id \
	!= 1 && next->id != 22)))
		return (throw_error(current));
	return (1);
}

t_list	*syntax_checker(t_list **tokens)
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
	return (*tokens);
}
