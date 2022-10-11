/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:21:31 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/06 14:49:10 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*the global var*/

/*libraries*/
# include "Libft/libft.h"
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
	int				fd[2];
	char			**args;
	char			*path;
}	t_cmd;
# include "Builtins/builtins.h"

/*functions*/
int			quote_check(char *s);
char		*new_prompt(void);
char		*getval(char *s1, t_env *env);
char		**get_paths(char **en);
void		history_reloader(int ac);
void		free_cmds(t_cmd **cmds);
void		ft_exit(char **cmd);
void		editor(char **s1, char *s2);
void		get_history(char *s, long long int n);
void		file_handler(t_list *token, int *fd_in, int *fd_out, int cmd_id, t_env *env);
void		param_extractor(t_params **params, t_env *env, t_list *input);
t_list		*tokenizer(char *s, int i, int j, t_env *env);
t_list		*syntax_checker(t_list **tokens, t_env *env);
t_list		*getter(t_list **tokens, t_env *env);
t_cmd		**cmd_extractor(t_list *input, t_env *env);
void		rl_replace_line(const char *text, int clear_undo);
#endif