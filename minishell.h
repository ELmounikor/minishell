/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:21:31 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/21 09:50:26 by mel-kora         ###   ########.fr       */
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
int			quote_check(char *s);
char		*new_prompt(void);
char		*getval(char *s1, t_env *env, t_list **token);
char		*get_nd_split(t_list **token, char *value, t_env *env, int i);
char		**get_paths(char **en);
void		history_reloader(int ac);
void		free_cmds(t_cmd **cmds);
void		ft_exit(char **cmd);
void		get_history(char *s, long long int n, int outfd);
void		rl_replace_line(const char *text, int clear_undo);
int			here_doc(t_list *token, int cmd_id, char **file_name, t_env *env);
int			handle_file(char *file_name, char code, int fd);
t_list		*tokenizer(char *s, int i, int j, t_env *env);
t_list		*syntax_checker(t_list **tokens, t_env *env);
t_list		*getter(t_list **tokens, t_env *env);
t_cmd		**cmd_extractor(t_list *input, t_env *env);
#endif