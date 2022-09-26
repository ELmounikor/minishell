/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:38:33 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/26 19:27:15 by sennaama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int main(int argc, char **argv, char **envp)
{
    if (argc < 1)
        return (0);
    //echo(argv);
    //cd(argv);
    (void)argv;
    t_env *env;
    env = get_env(envp);
    export(argc, argv, env);
    printf("\n\n\n");
    print_env(env);
    //export(argv, e);
    return (1);
}