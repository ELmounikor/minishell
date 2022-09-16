/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:11:29 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/16 17:25:01 by mounikor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_extarctor(char *s)
{
	t_list	*input;
	t_cmd	*cmds;

	input = getter(tokenizer(s, 0, 0), env);
	cmds = NULL;
	return (cmds);
}

