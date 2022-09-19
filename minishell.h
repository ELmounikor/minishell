/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:21:31 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/19 21:26:03 by mounikor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*libraries*/
# include "Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/*structers*/
typedef struct s_env
{
	char	**env;
	char	**paths;
	int		cmd_count;
}	t_env;

typedef struct s_cmd
{
	char			**args;//cmd and its arguments
	char			*path;//cmd executabel path
	char			*limiter;//use when file_fd[0] = -444 in here_doc(limiter)
	int				file_des[2];//in and out file descriptors default 0 -> la l9iti chi haja mn ghir 0 overidi l corresponing pipe end with the corresponding fd
}	t_cmd;

/*functions*/
int		quote_check(char *s);
char	*new_prompt(void);
void	history_reloader(int ac);
void	free_cmds(t_cmd **cmds);
void	history(char **cmd);
void	ft_exit(char **cmd);
void	get_history(char *s, long long int n);
t_list	*tokenizer(char *s, int i, int j);
t_list	*syntax_checker(t_list **tokens);
t_list	*getter(t_list *tokens, t_list *env);
t_list	*env_starter(char **envi, int i);
t_env	*env_extractor(t_list *envi, t_list *input);
t_cmd	*cmd_extractor(t_list *input);
#endif