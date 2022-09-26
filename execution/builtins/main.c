/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sennaama <sennaama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:38:33 by sennaama          #+#    #+#             */
/*   Updated: 2022/09/26 15:50:14 by sennaama         ###   ########.fr       */
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
    export(argv, env);
    print_env(env);
    //export(argv, e);
    return (1);
}