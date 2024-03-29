/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/21 17:20:39 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*token_maker(char *s, int start, int finish, int id)
{
	t_list	*token;
	char	*str;
	int		i;

	if (id != 1 && s[finish + 1] && !ft_isspace(s[finish + 1]) && \
	s[finish + 1] != '|' && s[finish + 1] != '>' && s[finish + 1] != '<')
		id *= 10;
	if (id != 5 && id != 6 && id != 50 && id != 60)
		finish++;
	if (finish == start)
		return (ft_lstnew(ft_strdup(""), id));
	str = (char *) malloc (finish - start + 1);
	if (!str)
		return (0);
	i = 0;
	while (start < finish)
		str[i++] = s[start++];
	str[i] = 0;
	if ((id == 5 || id == 6 || id == 50 || id == 60))
		token = ft_lstnew(ft_strdup(str), id);
	else
		token = ft_lstnew(ft_strtrim(str, " <>"), id);
	free(str);
	return (token);
}

int	lexer(char c, char next_c, int *id)
{
	int			i;

	i = 0;
	if (!id)
		id = &i;
	if (c == '|')
		*id = 1;
	else if (c == '$' && next_c == '?')
		*id = 33;
	else if (c == '$' && (ft_isalnum_(next_c) || next_c == 34 || next_c == 39))
		*id = 3;
	else if (c == '<' && next_c == '<')
		*id = 44;
	else if (c == '<')
		*id = 4;
	else if (c == '>' && next_c == '>')
		*id = 77;
	else if (c == '>')
		*id = 7;
	if (*id > 10)
		return (1);
	else if (*id > 0)
		return (0);
	return (-1);
}

t_list	*get_token(char *s, int *start, int *end, int id)
{
	if (*start == *end)
	{
		while (s[*end] && !ft_isspace(s[*end]) && s[*end] != 39 && \
		s[*end] != 34 && id != 1 && !(id == 3 && !ft_isalnum_(s[*end])))
		{
			if (lexer(s[*end], s[*end + 1], 0) != -1)
			{
				if (*start != *end)
					break ;
				*end += lexer(s[*end], s[*end + 1], &id);
			}
			(*end)++;
		}
		if (!id && s[*end] && (s[*end] == 39 || s[*end] == 34 || \
		s[*end] == '$'))
			return (token_maker(s, *start, *end - 1, 10));
		else
			return (token_maker(s, *start, *end - 1, id));
	}
	else if (s[*start] == 39)
		return (token_maker(s, *start + 1, (*end)++, 5));
	else if (s[*start] == 34)
		return (token_maker(s, *start + 1, (*end)++, 6));
	return (0);
}

void	check_max_heredoc(t_list *tokens)
{
	int	n_heredoc;

	n_heredoc = 0;
	while (tokens && n_heredoc <= 16)
	{
		if (tokens->id == 44 || tokens->id == 440)
			n_heredoc++;
		tokens = tokens->next;
	}
	if (n_heredoc > 16)
	{
		ft_putstr_fd("sh-sm: maximum here-document count exceeded\n", 2);
		exit(2);
	}
}

t_list	*tokenizer(char *s, int i, int j, t_env *env)
{
	t_list	*tokens;
	int		q[2];

	tokens = NULL;
	while (s && s[i])
	{
		q[0] = 0;
		q[1] = 0;
		while (s[i] && ft_isspace(s[i]))
			i++;
		j = i;
		while (s[i] && (s[i] == 34 || s[i] == 39 || q[0] % 2 || q[1] % 2))
		{
			if (s[i] && s[i] == 34 && q[1] % 2 == 0)
				q[0]++;
			else if (s[i] && s[i] == 39 && q[0] % 2 == 0)
				q[1]++;
			if ((q[1] % 2 == 0 && q[0] % 2 == 0))
				break ;
			i++;
		}
		ft_lstadd_back(&tokens, get_token(s, &j, &i, 0));
	}
	check_max_heredoc(tokens);
	return (syntax_checker(&tokens, env));
}
