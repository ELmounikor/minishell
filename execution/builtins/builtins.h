/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:15:10 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/26 19:45:23 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include<unistd.h>
# include<stdio.h>
# include<dirent.h>
# include "../ft_pipex/pipex.h"

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	echo(char **argv);
void	cd(char **argv);
t_env	*get_env(char **en);
void	export(int argc, char **cmd, t_env *envp);
void	print_env(t_env	*env);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
t_env	*ft_lstnew_env(char *variable, char *value);
t_env	*ft_lstlast_env(t_env *lst);
int		*count_words(char	*str, char c);
char	**ft_split_env(char *str, char c);
void	add_element(char *s1, char *s2, t_env **envp);
void	add_env(char **f, t_env **envp);
t_env	*ft_copy_env(t_env *env);
#endif
