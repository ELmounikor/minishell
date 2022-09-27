/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:03:42 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/27 01:02:38 by mel-kora         ###   ########.fr       */
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
/*
	if (!ft_strncmp(s1, "?", 2))
		return (ft_itoa(last_exit_code));*/
	
	printf("before%s=%s\n", s1, env->value);
	while (env && s1)
	{
		if (!ft_strncmp(s1, env->variable, ft_strlen(s1)))
		{
			printf("after%s=%s\n", s1, env->value);
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
	if (token->id && token->id % 3 == 0 && j != 44 && j != 440)
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
				while (ft_isalnum_(token->content[i]))
					i++;
				editor(&s, getval(ft_substr(token->content, j, i - j), env));
			}
		}
		return (s);
	}
	return (ft_strdup(token->content));
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
		if ((token->id == 4 || token->id == 44 || token->id == 7 || \
		token->id == 77) && !token->content && token->next)
			token = token->next;
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
	return (syntax_checker(&input));
}
