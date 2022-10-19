/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:53:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/19 17:53:04 by sennaama         ###   ########.fr       */
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
	t_data		data;
	t_cmd		**cmd;
	char		*s;

	av = NULL;
	data.env = get_env(en);
	data.pwd = ft_strdup(getenv("PWD"));
	g_exit_value = 0;
	history_reloader(ac);
	//ft_envclear(&(data.env), &free);
	while (1)
	{
		signal(SIGINT, handler_sig);
		signal(SIGQUIT, handler_sig);
		s = new_prompt();
		input = tokenizer(s, 0, 0, data.env);
		cmd = cmd_extractor(input, data.env);
		// //cmdprint(cmd);
		if (cmd)
			ft_pipe(cmd, cmd_count(input), &data);
		free_cmds(cmd);
		ft_lstclear(&input, &free);
		ft_free(&s);
		// printf("\n==================================================\n");
		// system("leaks minishell");
		// printf("\n==================================================\n");
	}
	//ft_envclear(&data.env, &free);
	//free(data.pwd);
	return (0);
}
