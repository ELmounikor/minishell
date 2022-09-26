/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kora <mel-kora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:00:04 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/26 22:05:46 by mel-kora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main1(int argc, char **argv, char **envp)
{
	int		child_1;
	pid_t	child_2;
	int		fd[2];

	if (argc != 5)
		printf("error");
	if (pipe(fd) == -1)
		return (1);
	child_1 = fork();
	if (child_1 == 0)
		cmd_child1(argv, envp, fd);
	child_2 = fork();
	if (child_2 == 0)
		cmd_child2(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(child_1,NULL,0);
	waitpid(child_2,NULL,0);
}
