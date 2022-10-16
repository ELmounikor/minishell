/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:37:34 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/24 17:49:16 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_close(int argc, int **fd)
{
	int i;
	
	i = 0;
	while(i < argc)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}
int main1(int argc, char **argv, char **envp)
{
    int	**fd;
    int	i;
	int id[argc];
	
	char **options;
	char *path;
    
	argv++;
	argc--;
    fd = (int **)malloc((argc - 1) * (sizeof(int *)));
	if (!fd)
		ft_perror("fg");
	i = 0;
	while (i < argc)
	{
		fd[i] = (int *)malloc(2 * sizeof(int));
		if (!fd[i])
			ft_perror("error");
		i++;
	}
	i = 0;
	/*fd_in = open(argv[0], O_RDONLY, 0777);
	if (fd_in < 0)
		ft_perror(argv[0]);
	fd_out = open(argv[argc - 1],O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_in < 0)
		ft_perror(argv[argc - 1]);*/
	while(i < argc - 1)
	{
		if (pipe(fd[i]) < 0)
			ft_perror("pipe");
		i++;
	}
	i = 0;
	while (i < argc)
	{
		id[i] = fork();
		if (id[i] == 0)
		{
			if (i == 0)
			{
				options = ft_split(argv[i], ' ');
				path = get_cmd_path(options[0]);
				if (path ==  NULL)
					ft_perror(argv[i]);
				//dup2(, STDIN_FILENO);
				dup2(fd[i][1], STDOUT_FILENO);
				ft_close(argc -1, fd);
				execve(path, options, envp);
			}
			else if(i == argc - 1)
			{
				options = ft_split(argv[i], ' ');
				path = get_cmd_path(options[0]);
				if (path ==  NULL)
					ft_perror(argv[i]);
				dup2(fd[i - 1][0], STDIN_FILENO);
				//dup2(fd_out, STDOUT_FILENO);
				ft_close(argc -1, fd);
				execve(path, options, envp);
			}
			else
			{
				options = ft_split(argv[i], ' ');
				path = get_cmd_path(options[0]);
				if (path ==  NULL)
					ft_perror(argv[i]);
				dup2(fd[i - 1][0], STDIN_FILENO);
				dup2(fd[i][1], STDOUT_FILENO);
				ft_close(argc - 1, fd);
				execve(path, options, envp);
			}
		}
		//printf("%d\n", i);
		i++;
	}
	ft_close(argc - 1, fd);
	
	i = 0;
	while(i < argc)
	{
		waitpid(id[i],NULL,0);
		i++;
	}
}
