/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:53:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/27 01:07:17 by mel-kora         ###   ########.fr       */
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
	free_cmds(cmd);
	ft_lstclear(input, &free);
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
	//history_reloader(ac); // messup up & down keys tanchofoha apres
	while (1)
	{
		s = new_prompt();
		//params = (t_params *) malloc (sizeof(t_params));
		input = tokenizer(s, 0, 0, env);
		if (input)
		{
			//param_extractor(&params, env, input);// env_extractor(&params, NULL, NULL); //env to be updated in between child processes using
			cmd = cmd_extractor(input);
			int i = 0;
			printf("\n=============cmd data============\n");
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
				//aslan dima null lol khlito lik bach t3mrih kima taf9na <3\n---------------------------------\n", \
				cmd[i]->file_des[0], cmd[i]->file_des[1], cmd[i]->limiter, cmd[i]->path);
				i++;
			}
			// excute cmds here
			free_all(NULL, cmd, &input);
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