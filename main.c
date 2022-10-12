/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:53:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/12 18:19:49 by mel-kora         ###   ########.fr       */
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

void	free_all(t_params *params, t_cmd **cmd, t_list **input)
{
	ft_lstclear(input, &free);
	free_cmds(cmd);
	if (params)
	{
		ft_split_cleaner(params->paths);
		ft_split_cleaner(params->en);
		free(params);
	}
}

int	main(int ac, char **av, char **en)
{
	t_list		*input;
	t_env		*env;
	t_cmd		**cmd;
	//t_params	*params;
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
			//param_extractor(&params, env, input);// env_extractor(&params, NULL, NULL); //env to be updated in between child processes using
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
			//excute cmds here
			ft_pipe(cmd, cmd_count(input), env);
			free_cmds(cmd);
			ft_lstclear(&input, &free);
			// free_all(0, cmd, &input);
		}
		
		ft_free(&s);
		// printf("\n==================================================\n");
		// system("leaks minishell");
		// printf("\n==================================================\n");
	}
	ft_envclear(&env, &free);
	return (0);
}
// printf("=============params data============\nnumber of cmd = %d\nlast exit code = %d\n--------------env list-------------\n", params->cmd_count, params->last_exit_code);
// t_env *tmp;
// tmp = env;
// while (tmp)
// {
// 	printf("%s=%s\n", tmp->variable, tmp->value);
// 	tmp = tmp->next;
// }
// i = 0;
// printf("--------------env list-------------\n");
// while (params->en && params->en[i])
// 	printf("%s\n", params->en[i++]);