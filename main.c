/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:53:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/16 15:29:12 by mounikor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd)
{
	if (!cmd)
	{
		printf("exit\n");
		exit(0);
	}
}

t_list	*env_extractor(char **envi, int i)
{
	t_list	*env;

	i = 0;
	env = NULL;
	while (envi[i])
		ft_lstadd_back(&env, ft_lstnew(ft_strdup(envi[i++]), 0));
	return (env);
}

char	*new_prompt(void)
{
	char	*s;
	int		h;

	write(1, "🤖sh-sm$ ", 12);
	s = readline(NULL);
	if (!s)
		ft_exit(NULL);
	h = open("Libft/.sh_history", O_RDWR | O_APPEND | O_CREAT, 0666);
	write(h, s, ft_strlen(s));
	write(h, "\n", 1);
	add_history(s);
	close(h);
	if (!quote_check(s))
	{
		printf("This command has unclosed quotes >_<\n");
		ft_free(&s);
		return (0);
	}
	return (s);
}

int	main(int ac, char **av, char **envi)
{
	t_list		*input;
	t_list		*env;
	// t_cmd		*cmds;
	t_list		*test;
	char		*s;

	av = NULL;
	// history_reloader(ac);//messup up & down keys tanchofoha apres
	env = env_extractor(envi, ac);
	while (1)
	{
		s = new_prompt();
		if (s)
		{
			input = getter(tokenizer(s, 0, 0), env);
			test = input;
			while (test)
			{
				printf("id = %d, content = %s\n", test->id, test->content);
				test = test->next;
			}
			ft_lstclear(&input, &free);
			ft_free(&s);
		}
		// system("leaks minishell");
	}
	envi = NULL;
}
