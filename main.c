/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:53:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/23 12:08:14 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(char **cmd)
{
	if (!cmd)
	{
		printf("exit\n");
		exit(0);
	}
}

char *new_prompt(void)
{
	char *s;
	int h;

	// write(1, "🤖sh-sm$ ", 12);
	s = readline("🤖sh-sm$ ");
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

int main(int ac, char **av, char **envi)
{
	t_list	*input;
	t_list	*env_i;
	t_cmd	**cmds;
	//t_env	*env;
	char	*s;
	//t_list	*test;//to be removed

	av = NULL;
	//history_reloader(ac); // messup up & down keys tanchofoha apres
	env_i = env_starter(envi, ac);
	while (1)
	{
		s = new_prompt();
		input = getter(tokenizer(s, 0, 0), env_i);
		if (input)
		{/*
			// for token testing
			test = input;
			while (test)
			{
				printf("id = %d, content = %s\n", test->id, test->content);
				test = test->next;
			}*/
			cmds = cmd_extractor(input);
			//env = env_extractor(env_i, input);//need to be updated if cmd == export || unset ;3 can be udated using (env, NULL, NULL)
			// excute cmds here
			if (cmds)
				free_cmds(cmds);
			ft_lstclear(&input, &free);
			ft_free(&s);
		}
		// system("leaks minishell");
	}
	ft_lstclear(&env_i, &free);
	return (0);
}
