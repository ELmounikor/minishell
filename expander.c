/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:03:42 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/14 18:16:47 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	editor(char **s1, char *s2)
{
	char	*tmp;

	tmp = s2;
	ft_free(s1);
	*s1 = tmp;
}

char	*getval(char *s1, t_list *env)
{
	char	**dic;

	while (env)
	{
		dic = ft_split(env->content, '=');
		if (!ft_strncmp(s1, dic[0], ft_strlen(s1) + 1))
		{
			ft_split_cleaner(dic);
			return (ft_substr(env->content, ft_strlen(s1) + 1, \
			ft_strlen(env->content)));
		}
		ft_split_cleaner(dic);
		env = env->next;
	}
	return (0);
}

char	*expander(t_list *token, t_list *env, int i, int j)
{
	char	*s;

	s = NULL;
	if (token->id == 6 || token->id == 60 || token->id == 3)
	{
		while (token->content[i])
		{
			j = i;
			while (token->content[i] && !(token->content[i] == '$' && \
			ft_isalnum_(token->content[i + 1])))
				i++;
			editor(&s, ft_strjoin(s, ft_substr(token->content, j, i - j)));
			if (token->content[i] == '$')
			{
				j = ++i;
				while (ft_isalnum_(token->content[i]))
					i++;
				editor(&s, ft_strjoin(s, \
				getval(ft_substr(token->content, j, i - j), env)));
			}
		}
		return (s);
	}
	return (ft_strdup(token->content));
}

t_list	*getter(t_list *token, t_list *env)
{
	t_list	*input;
	t_list	*start;
	char	*s;
	int		id;

	start = token;
	input = NULL;
	while (token)
	{
		id = token->id;
		if ((token->id == 4 || token->id == 44 || token->id == 7 || \
		token->id == 77) && !token->content && token->next)
			token = token->next;
		s = expander(token, env, 0, 0);
		while (token->id && token->id % 10 == 0)
		{
			editor(&s, ft_strjoin(s, expander(token->next, env, 0, 0)));
			token = token->next;
			id = 0;
		}
		ft_lstadd_back(&input, ft_lstnew(s, id));
		token = token->next;
	}
	ft_lstclear(&start, &free);
	return (syntax_checker(&input));
}
