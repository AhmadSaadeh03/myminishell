/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/03/24 14:53:00 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishill.h"

int main(void)
{
    t_minishell *shell = NULL;

    shell = init_shell(shell);
    if (!shell)
    {
        printf("ERROR:%s \n", "fail allocation of shell");
        exit(1);
    }
    while (1)
    {
        shell->name = readline("👾 Minihell> ");
        if(*(shell->name) == '\0')
        {
            free(shell->name);
            continue ;
        }
        add_history(shell->name);
        if (split(shell) == 1)
            return 1;
            //free_minishell(shell);
        expand(shell);
        free(shell->name);
    }
    free_and_exit(shell);
    return (0);
}
