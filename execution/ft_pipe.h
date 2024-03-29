/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:37:08 by sennaama          #+#    #+#             */
/*   Updated: 2022/10/24 12:58:35 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPE_H
# define FT_PIPE_H
# include "../minishell.h"
# include <unistd.h>
# include "../Builtins/builtins.h"
# include <signal.h>
# include <errno.h>

int		g_exit_value;
int		**pipe_fd(int nbr_cmd);
void	ft_close(int argc, int **fd);
char	**get_env_char(t_env *env);
void	ft_dup(t_cmd *cmd, int i, int nbr_cmd, int **fd);
void	ft_pipe(t_cmd **cmd, int nbr_cmd, t_data *data);
char	*ft_get_path(char *arg, t_env *env);
void	handler_sig(int signum);
void	handler_child(int sig);
void	handler_fake(int sig);
void	ft_free_char(char **p);
#endif