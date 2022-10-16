/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonuso.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:29:12 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/27 14:52:12 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int main3(int argc, char **argv, char **envp)
// {
//     int	fd[2 * (argc - 1)];
// 	int	fd_in;
// 	int	fd_out;
// 	int id;
// 	int	i;

// 	i = 0;
// 	while (i < argc - 1)
// 	{
// 		pipe(fd + i);
// 		i += 2;
// 	}
// 	fd_in = open(argv[1], O_RDONLY ,0777);
// 	fd_out = open(argv[argc - 1],O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	i = 0;
// 	while (i < argc)
// 	{
// 		id = fork();
// 		if (id)
// 		if (i == 1)
// 		{
// 			dup2(fd_in, STDIN_FILENO);
// 			dup2(fd[1], STDOUT_FILENO);
// 		}
// 		else if (i == argc - 1)
// 		{
// 			dup2(fd[1], STDIN_FILENO);
// 			dup2(fd[0], STDOUT_FILENO);
// 		}
// 	}
// 	while (wait(NULL));
// }
void	ft_close(int id, int **fd, int argc)
{
	if (id > 1)
	{
		close(fd[id - 2][0]);
		close(fd[id - 2][1]);
	}	
	else if (id == argc)
	{
		close(fd[id - 2][0]);
		close(fd[id - 2][1]);
	}
}

int main(int argc, char **argv, char **envp)
{
	int 	**fd;
	int		i;
	t_list *l;
	int		id;
	int		fd_in;
	int		fd_out;
	char 	**options;
	char	*path;
	t_list *tmp;
	int		n;

	fd = (int **)malloc((argc - 3) * sizeof(int *));
	if (!fd)
		ft_perror("error");
	i = 0;
	while (i < argc - 1)
	{
		fd[i] = (int *)malloc(2 * sizeof(int));
		if (!fd[i])
			ft_perror("error");
		i++;
	}
	l = NULL;
	argv++;
	argc = argc - 1;
	l = ft_list_init(argv);
	fd_in = open(l->content, O_RDONLY, 0777);
	if (fd_in < 0)
		ft_perror(l->content);
	fd_out = open(get_content(l, argc - 1),O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd_in < 0)
		ft_perror(get_content(l, argc - 1));
	i = 1;
	tmp = l;
	tmp = tmp->next;
	n = 0;
	while (i < argc)
	{
		id = fork();
		if (tmp->next != NULL)
		{
			pipe(fd[n]);
			printf("hbk\n");
		}
		if (id == 0)
		{
			if (n == 0)
			{
				options = ft_split(tmp->content, ' ');
				path = get_cmd_path(options[0]);
				if (path ==  NULL)
					ft_perror(tmp->content);
				dup2(fd_in, STDIN_FILENO);
				dup2(fd[n][1], STDOUT_FILENO);
				execve(path, options, envp);
			}
			else if(n == argc - 2)
			{
				options = ft_split(get_content(l, i - 1), ' ');
				printf("%s\n",get_content(l, i - 1));
				path = get_cmd_path(options[0]);
				if (path ==  NULL)
					ft_perror(get_content(l, i - 1));
				dup2(fd[n - 1][0], STDIN_FILENO);
				dup2(fd_out, STDOUT_FILENO);
				execve(path, options, envp);
			}
			else
			{
				dup2(fd[n - 1][0], STDIN_FILENO);
				dup2(fd[n][1], STDOUT_FILENO);
				options = ft_split(tmp->content, ' ');
				path = get_cmd_path(options[0]);
				if (path ==  NULL)
					ft_perror(tmp->content);
				execve(path, options, envp);
			}
			ft_close(n, fd, argc);
		}
		ft_close(n, fd, argc);
		tmp = tmp->next;
		i++;
		n++;
	}
//	ft_close(n, fd, argc);
	close(fd_in);
	close(fd_out);
	//ft_free_list(&l);
	//system("leaks pipex");
}