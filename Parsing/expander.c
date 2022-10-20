/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:03:42 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/20 17:55:57 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*getval(char *s1, t_env *env, t_list **token)
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
			if (*token && ((*token)->id == 3 || (*token)->id == 30))
				return (get_nd_split(token, env->value, env, 0));
			return (ft_strdup(env->value));
		}
		env = env->next;
	}
	ft_free(&s1);
	return (0);
}

void	expander(t_list **t, t_env *env, char **s, int i)
{
	int	j;

	while ((*t)->content && (*t)->content[i])
	{
		j = i;
		while ((*t)->content[i] && !((*t)->content[i] == '$' && (\
		ft_isalnum_((*t)->content[i + 1]) || (*t)->content[i + 1] \
		== '?')))
			i++;
		editor(s, ft_substr((*t)->content, j, i - j));
		if ((*t)->content[i] == '$')
		{
			j = ++i;
			while ((ft_isalnum_((*t)->content[i]) && (*t)->content[j] != \
			'?') || (i == j && (*t)->content[j] == '?'))
				i++;
			editor(s, getval(ft_substr((*t)->content, j, i - j), env, t));
		}
	}
}

char	*check_expand(t_list **t, t_env *env, int i, int *j)
{
	char	*s;

	s = NULL;
	if ((*t)->id && !((*t)->id % 3) && *j % 44 && \
	(*j == 30 || (*t)->content[i]))
	{
		expander(t, env, &s, i);
		if (!s && *j && *j % 100 && !(*j % 4 && *j % 7))
		{
			*j = -*j;
			s = ft_strdup((*t)->content);
		}
		return (s);
	}
	return (ft_strdup((*t)->content));
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
	else if (!(*token)->id && (*token)->content && !(*token)->content[0])
		(*token) = (*token)->next;
}

t_list	*getter(t_list **in, t_env *env)
{
	t_list	*input;
	t_list	*token;
	char	*s;
	int		id;

	token = *in;
	input = NULL;
	while (token && token->id >= 0)
	{
		id = token->id;
		check_redirection(&id, &token);
		if (!token)
			break ;
		s = check_expand(&token, env, 0, &id);
		while (token->id && token->id % 10 == 0)
		{
			editor(&s, check_expand(&token->next, env, 0, &id));
			token = token->next;
		}
		ft_lstadd_back(&input, ft_lstnew(s, id));
		token = token->next;
	}
	ft_lstclear(in, &free);
	return (input);
}
