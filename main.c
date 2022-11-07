/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:53:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/11/07 10:28:17 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *cmd)
{
	if (!cmd)
	{
		printf("exit\n");
		if (g_exit_value == 258)
			exit(2);
		exit(g_exit_value);
	}
}

char	*new_prompt(void)
{
	char	*s;
	int		h;

	s = readline("🤖sh-sm$ ");
	if (!s)
		ft_exit(NULL);
	if (s && s[0])
	{
		h = open("/tmp/.sh-sm_history", O_RDWR | O_APPEND | O_CREAT, 0666);
		write(h, s, ft_strlen(s));
		write(h, "\n", 1);
		add_history(s);
		close(h);
	}
	if (!quote_check(s))
	{
		ft_putstr_fd("sh-sm: unclosed quotes detected >_<\n", 2);
		ft_free(&s);
		return (0);
	}
	return (s);
}

void	sm_sh_init(int ac, char **av, char **en, t_data	*data)
{
	char	**i_cmd;
	int		pid;

	i_cmd = (char **) malloc (3 * sizeof(char *));
	if (i_cmd)
	{
		i_cmd[0] = ft_strdup("stty");
		i_cmd[1] = ft_strdup("-echoctl");
		i_cmd[2] = 0;
		pid = fork();
		if (pid == 0)
		{
			execve("/bin/stty", i_cmd, en);
			exit(0);
		}
		while (wait(NULL) != -1)
			;
		ft_split_cleaner(i_cmd);
	}
	(*data).env = get_env(en);
	(*data).pwd = ft_strdup(getenv("PWD"));
	g_exit_value = 0;
	history_reloader(ac);
	(void) av;
}

int	main(int ac, char **av, char **en)
{
	t_list		*input;
	t_data		data;
	t_cmd		**cmd;
	char		*s;

	sm_sh_init(ac, av, en, &data);
	while (1)
	{
		signal(SIGINT, handler_sig);
		signal(SIGQUIT, handler_sig);
		s = new_prompt();
		input = tokenizer(s, 0, 0, data.env);
		cmd = cmd_extractor(input, data.env);
		if (cmd && cmd[0])
			ft_pipe(cmd, cmd_count(input), &data);
		free_cmds(cmd);
		ft_lstclear(&input, &free);
		ft_free(&s);
	}
	ft_envclear(&data.env, &free);
	free(data.pwd);
	return (0);
}
