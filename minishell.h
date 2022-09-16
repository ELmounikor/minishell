/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mounikor <mounikor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:21:31 by mel-kora          #+#    #+#             */
/*   Updated: 2022/09/16 17:23:28 by mounikor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*libraries*/
# include "Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/*structers*/
typedef struct s_env
{
	char	**env;
	int		cmd_count;
}	t_env;

typedef struct s_cmd
{
	char			*path;
	char			**args;
	int				file_des[2];
	int				pipe_des[2];
}	t_cmd;

/*functions*/
int		quote_check(char *s);
char	*new_prompt(void);
void	history_reloader(int ac);
void	history(char **cmd);
void	ft_exit(char **cmd);
void	get_history(char *s, long long int n);
t_list	*tokenizer(char *s, int i, int j);
t_list	*syntax_checker(t_list **tokens);
t_list	*getter(t_list *tokens, t_list *env);
#endif