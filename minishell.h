/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:21:31 by mel-kora          #+#    #+#             */
/*   Updated: 2022/07/25 08:18:26 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*libraries*/
# include "Libft/libft.h"

/*structers*/
typedef struct s_env
{
	char	**env;
	int		filedes[2];
	int		count;
}	t_env;

typedef struct s_cmd
{
	char	*path;
	char	**args;
	int		fd[2];
}	t_cmd;

/*functions*/
char	*write_history(void);
void	get_history(char *s, long long int n);
#endif