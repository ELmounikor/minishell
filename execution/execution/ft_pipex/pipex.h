/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:07:32 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/25 17:53:02 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_list
{
	char			*content;
	int				index;
	struct s_list	*next;
}	t_list;

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
