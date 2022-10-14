/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:03:42 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/14 13:59:51 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	editor(char **s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(*s1, s2);
	ft_free(&s2);
	ft_free(s1);
	*s1 = tmp;
}

char	*getval(char *s1, t_env *env)
{
	if (!ft_strcmp(s1, "?"))
	{
		ft_free(&s1);
		return (ft_itoa(g_exit_value));
	}
	else if (!ft_strcmp(s1, "0"))
	{
		ft_free(&s1);
		return (ft_strdup("sh-sm"));
	}
	while (env && s1)
	{
		if (!ft_strcmp(s1, env->variable))
		{
			ft_free(&s1);
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	ft_free(&s1);
	return (0);
}

char	*expander(t_list *token, t_env *env, int i, int j)
{
	char	*s;

	s = NULL;
	if (token->id && token->id % 3 == 0 && j % 44 != 0)
	{
		while (token->content && token->content[i])
		{
			j = i;
			while (token->content[i] && !(token->content[i] == '$' && (\
			ft_isalnum_(token->content[i + 1]) || token->content[i + 1] \
			== '?')))
				i++;
			editor(&s, ft_substr(token->content, j, i - j));
			if (token->content[i] == '$')
			{
				j = ++i;
				while ((ft_isalnum_(token->content[i]) && token->content[j] != \
				'?') || (i == j && token->content[j] == '?'))
					i++;
				editor(&s, getval(ft_substr(token->content, j, i - j), env));
			}
		}
		return (s);
	}
	return (ft_strdup(token->content));
}

void	check_redirection(int *id, t_list **token)
{
	if (((*token)->id == 4 || (*token)->id == 44 || (*token)->id == 7 || \
	(*token)->id == 77 || (*token)->id == 40 || (*token)->id == 440 || \
	(*token)->id == 70 || (*token)->id == 770) && !(*token)->content && \
	(*token)->next)
		(*token) = (*token)->next;
	if ((*id == 44 || *id == 440) && ((*token)->id == 5 || (*token)->id == 6 || \
	(*token)->id == 50 || (*token)->id == 60 || (*token)->id == 100 || \
	(*token)->id == 30))
		*id *= 2;
}

t_list	*getter(t_list **in, t_env *env)
{
	t_list	*input;
	t_list	*token;
	char	*s;
	int		id;

	token = *in;
	input = NULL;
	while (token)
	{
		id = token->id;
		check_redirection(&id, &token);
		s = expander(token, env, 0, id);
		while (token->id && token->id % 10 == 0)
		{
			editor(&s, expander(token->next, env, 0, id));
			token = token->next;
		}
		ft_lstadd_back(&input, ft_lstnew(s, id));
		token = token->next;
	}
	ft_lstclear(in, &free);
	return (input);
}
