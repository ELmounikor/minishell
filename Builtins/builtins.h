/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:15:10 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/29 21:41:29 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include "../minishell.h"

void	history(char **cmd);
void	echo(char **argv);
void	cd(char **argv, t_env *env);
t_env	*get_env(char **en);
void	export(char **cmd, t_env *envp);
void	print_env(t_env	*env);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
t_env	*ft_lstnew_env(char *variable, char *value);
t_env	*ft_lstlast_env(t_env *lst);
int		*count_words(char	*str, char c);
char	**ft_split_env(char *str, char c);
void	add_element(char *s1, char *s2, t_env **envp);
void	add_env(char **f, t_env **envp, char *str);
t_env	*ft_copy_env(t_env *env);
int		ft_check_variable(char *sub);
void	unset(char **argv, t_env *env);
void	pwd(void);
int		ft_atoi_exit(const char *str, int *err);
void	ft_exitt(char	**args);
void	export_element(char *cmd, t_env *envp);
void	ft_remove_element_list(t_env **env, char *var);
char	*get_value(t_env *env, char *str);
void	ft_perror(char *str);
int		ft_builtins(char *args, t_cmd *cmd, t_env *env);
#endif
