/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:35:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/10/20 15:16:39 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*libraries*/
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

/*structers*/
typedef struct s_cmd
{
	int				fd[2];
	int				size;
	char			**args;
	char			*path;
}	t_cmd;

typedef struct s_list
{
	int				id;
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env	*env;
	char	*pwd;
}	t_data;
/*functions*/
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstnew(char *content, int id);
void			cmdprint(t_cmd **cmd);
void			lstprint(t_list *input);
void			ft_envclear(t_env **env, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_envdelone(t_env *lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_free(char **s);
void			ft_split_cleaner(char **output);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			**ft_nsplit(char const *s, char *c);
char			*str_edit(char *s);
char			*get_next_line(int fd);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_char(char const *s1, char const *s2, char c);
char			*ft_strnstr(const char *hay, const char *nee, int len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_itoa(int n);
char			*ft_readline(char *prompt);
char			ft_convert(char c, char s);
char			ft_unflag(char s, char *c);
int				*cmd_size(t_list *lst);
int				cmd_count(t_list *lst);
int				ft_lstsize(t_list *lst);
int				ft_envsize(t_env *env);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(char *s1, char *s2);
int				ft_isnum(char *s);
int				ft_isspace(int c);
int				ft_isalnum_(int c);
int				ft_isalnumstr(char *s);
int				ft_strlen(const char *s);
int				is_file(int id);
long long int	ft_atoi(const char *str);
#endif
