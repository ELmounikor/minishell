/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:21:31 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/26 22:20:13 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*libraries*/
# include "Libft/libft.h"
# include "Builtins/builtins.h"
# include <readline/readline.h>
# include <readline/history.h>

/*structers*/
typedef struct s_params
{
	int		cmd_count;
	int		last_exit_code;
	char	**paths;
	char	**en;
	t_env	*env;
}	t_params;

typedef struct s_cmd
{
	int				file_des[2];
	char			**args;
	char			*limiter;
	char			*path;
}	t_cmd;

/*functions*/
int			quote_check(char *s);
char		*new_prompt(void);
char		**get_paths(char **en);
void		history_reloader(int ac);
void		free_cmds(t_cmd **cmds);
void		ft_exit(char **cmd);
void		get_history(char *s, long long int n);
void		file_handler(t_list *token, int *fdin, int *fdout, char **limiter);
void		param_extractor(t_params **params, t_env *env, t_list *input);
t_list		*tokenizer(char *s, int i, int j, t_env *env);
t_list		*syntax_checker(t_list **tokens);
t_list		*getter(t_list **tokens, t_env *env);
t_cmd		**cmd_extractor(t_list *input);
void			ft_envclear(t_env **env, void (*del)(void*));
int				ft_envsize(t_env *env);
#endif