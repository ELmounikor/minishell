/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:07:32 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/26 22:03:26 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../../minishell.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

char	*get_cmd_path(char	*arg);
void	ft_free_char(char **p);
void	cmd_child1(char **argv, char **envp, int *fd);
void	cmd_child2(char **argv, char **envp, int *fd);
void	ft_perror(char *str);
t_list	*ft_list_init(char **en);
void	ft_free_list(t_list **l);
char	*get_content(t_list *l, int index);
t_list	*ft_lstnew(char *content, int index);
void	ft_lstadd_back(t_list **alst, t_list *new);
#endif
