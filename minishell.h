/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:21:31 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/24 19:03:43 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*libraries*/
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"
# include "Builtins/builtins.h"

/*functions*/
void		here_doc(t_list *token, int cmd_id, char **file_name, t_env *env);
void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);
void		get_history(char *s, long long int n, int outfd);
void		history_reloader(int ac);
void		free_cmds(t_cmd **cmds);
void		ft_exit(char *cmd);
int			file_handler(t_cmd **cmd, t_list *token);
int			quote_check(char *s);
int			is_file(t_list *token);
char		*get_nd_split(t_list **token, char *value, t_env *env, int i);
char		*getval(char *s1, t_env *env, t_list **token);
char		*new_prompt(void);
char		**get_paths(char **en);
t_list		*tokenizer(char *s, int i, int j, t_env *env);
t_list		*syntax_checker(t_list **tokens, t_env *env);
t_list		*getter(t_list **tokens, t_env *env);
t_cmd		**cmd_extractor(t_list *input, t_env *env);
#endif