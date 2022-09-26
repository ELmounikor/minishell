/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:53:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/26 16:02:40 by mel-kora         ###   ########.fr       */
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

char	*new_prompt(void)
{
	char	*s;
	int		h;

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

int	main(int ac, char **av, char **envi)
{
	t_list	*input;
	t_list	*env_i;
	t_cmd	**cmd;
	// t_env	*env;
	char	*s;

	av = NULL;
	//history_reloader(ac); // messup up & down keys tanchofoha apres
	env_i = env_starter(envi, ac);
	while (1)
	{
		s = new_prompt();
		input = tokenizer(s, 0, 0, env_i);
		if (input)
		{
			cmd = cmd_extractor(input);
			// affichage des commandes
			int i = 0;
			while (cmd && cmd[i])
			{
				printf("---------------------------------\ndata of the command number %d \
				\n//cmd and its argument's list:\n", i + 1);
				int j = 0;
				while (cmd[i]->args[j])
					printf("%s\n", cmd[i]->args[j++]);
				printf("//in and out file descriptors:\nin_fd = %d\
				//lakant chi haja mn ghir 0 rdih howa lread end dyal lpipe\nout_fd = %d\
				//lakant chi haja mn ghir 0 rdih howa lwrite end dyal lpipe\nlimiter = %s\
				//use when file_fd[0] = -444 in here_doc(limiter)\npath = %s\
				//aslan dima null lol khlito lik bach t3mrih <3\n---------------------------------\n", \
				cmd[i]->file_des[0], cmd[i]->file_des[1], cmd[i]->limiter, cmd[i]->path);
				i++;
			}
			// excute cmds here
			free_cmds(cmd);
			ft_lstclear(&input, &free);
		}
		ft_free(&s);
		printf("\n==================================================\n");
		system("leaks minishell");
		printf("\n==================================================\n");
	}
	ft_lstclear(&env_i, &free);
	return (0);
}
