/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:35:22 by mel-kora          #+#    #+#             */
/*   Updated: 2022/07/22 13:01:12 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

/*functions*/
void	ft_putstr_fd(char *s, int fd);
void	ft_split_cleaner(char **output);
void	ft_free(char **s);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strnstr(const char *haystack, const char *needle, int len);
char	*ft_strjoin_slash(char const *s1, char const *s2);
char	*str_edit(char *s);
char	ft_convert(char c);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);
#endif
