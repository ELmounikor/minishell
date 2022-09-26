/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:41:04 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/24 17:49:38 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(0);
}

void    cmd_child1(char **argv, char **envp, int *fd)
{
    char 	**options;
    char	*path;
    int		fd_in;     
    
    fd_in = open(argv[1], O_RDONLY ,0777);
	if (fd_in < 0)
		ft_perror(argv[1]);
    options = ft_split(argv[2], ' ');
	path = get_cmd_path(options[0]);
	if (path ==  NULL)
		ft_perror(argv[2]);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd_in);
	close(fd[0]);
	close(fd[1]);
	execve(path, options, envp);
}

void    cmd_child2(char **argv, char **envp, int *fd)
{
	char 	**options;
    char	*path;
    int		fd_out;     
    
	options = ft_split(argv[3], ' ');
	path = get_cmd_path(options[0]);
	if (path ==  NULL)
		ft_perror(argv[3]);
	fd_out = open(argv[4],O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_out < 0)
		ft_perror(argv[4]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execve(path, options, envp);
}
