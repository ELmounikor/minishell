/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:15:10 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/19 17:23:32 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include "../minishell.h"
# include "../execution/ft_pipe.h"

void	history(char **cmd);
void	echo(char **argv);
void	cd(char **argv, t_data *data);
t_env	*get_env(char **en);
void	export(char **cmd, t_env **envp);
void	print_env(t_env	*env);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
t_env	*ft_lstnew_env(char *variable, char *value);
t_env	*ft_lstlast_env(t_env *lst);
int		*count_words(char	*str, char c);
char	**ft_split_env(char *str, char c);
void	add_element(char *s1, char *s2, t_env **envp);
void	add_env(char **f, t_env **envp,int p);
t_env	*ft_copy_env(t_env *env);
int		ft_check_variable(char *sub);
void	unset(char **argv, t_env **env);
void	pwd(char *p);
int		ft_atoi_exit(const char *str, int *err);
void	ft_exitt(char	**args, int nbr_cmd);
void	export_element(char *cmd, t_env **envp);
void	ft_remove_element_list(t_env **env, char *var);
char	*get_value(t_env **env, char *str);
void	ft_perror(char *str);
int     ft_builtins(char *args, t_cmd *cmd, t_data *data, int nbr_cmd);
int     ft_exist_value(t_env *env, char *variable, char *value);
int     ft_exist(char *str, char c);
#endif
