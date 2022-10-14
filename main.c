/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:53:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/14 15:24:59 by mel-kora         ###   ########.fr       */
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

void	free_cmds(t_cmd **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = -1;
	while (cmd[++i])
	{
		ft_split_cleaner(cmd[i]->args);
		if (cmd[i]->fd[0] > 0)
			close(cmd[i]->fd[0]);
		if (cmd[i]->fd[1] > 0)
			close(cmd[i]->fd[1]);
		free(cmd[i]);
	}
	free(cmd);
	cmd = NULL;
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

int	main(int ac, char **av, char **en)
{
	t_list		*input;
	t_env		*env;
	t_cmd		**cmd;
	char		*s;

	av = NULL;
	ac = 0;
	env = get_env(en);
	g_exit_value = 0;
	//history_reloader(ac); // messup up & down keys tanchofoha apres
	while (1)
	{
		//printf("---%d\n", g_exit_value);
		signal(SIGINT, handler_sig);
		signal(SIGQUIT, handler_sig);
		s = new_prompt();
		input = tokenizer(s, 0, 0, env);
		cmd = cmd_extractor(input, env);
		if (cmd)
		{
			// int i = 0;
			// printf("\n=============cmd data============\n");
			// while (cmd && cmd[i])
			// {                
			// 	printf("---------------------------------\ndata of the command number %d \
			// 	\n//cmd and its argument's list:\n", i + 1);
			// 	int j = 0;
			// 	while (cmd[i]->args[j])
			// 		printf("%s\n", cmd[i]->args[j++]);
			// 	printf("%s\n", cmd[i]->args[j]);
			// 	printf("//in and out file descriptors:\nin_fd = %d\
			// 	//lakant chi haja mn ghir 0 rdih howa lread end dyal lpipe\nout_fd = %d\
			// 	//lakant chi haja mn ghir 0 rdih howa lwrite end dyal lpipe\n<3\n---------------------------------\n", \
			// 	cmd[i]->fd[0], cmd[i]->fd[1]);
			// 	//ft_builtins(cmd[i], env);
			// 	i++;
			// }
			ft_pipe(cmd, cmd_count(input), env);
			free_cmds(cmd);
			ft_lstclear(&input, &free);
		}
		
		ft_free(&s);
		// printf("\n==================================================\n");
		// system("leaks minishell");
		// printf("\n==================================================\n");
	}
	ft_envclear(&env, &free);
	return (0);
}