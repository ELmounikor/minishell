/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:02:20 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/24 19:06:15 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"builtins.h"

void    cd(char **argv)
{
    char    *path;
    
    if (argv[2] == NULL)
        chdir(getenv("HOME"));
    else if (chdir(argv[2]) != 0) 
        ft_perror(argv[2]);
    path = getcwd(NULL, 0);
    printf("%s\n", path);
}
