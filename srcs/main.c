/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:32:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/04/28 20:47:08 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_free_env_list(t_env *head)
{
    t_env	*temp;

    while (head)
    {
        temp = head;
        head = head->next;
        if (temp->env_name)
            free(temp->env_name);
        if (temp->value)
            free(temp->value);
        free(temp);
    }
}
void free_cmd_Aaa(t_cmd *cmd)
{
    t_cmd *temp;

    while (cmd)
    {
        temp = cmd;
        cmd = cmd->next;

        if (temp->cmd_line)
        {
            for (int i = 0; temp->cmd_line[i]; i++)
                free(temp->cmd_line[i]);
            free(temp->cmd_line);
        }
        if (temp->redirect)
            free(temp->redirect);
        if (temp->file_in)
            free(temp->file_in);
        if (temp->file_out)
            free(temp->file_out);
        if (temp->limiter)
            free(temp->limiter);

        free(temp);
    }
}

int main(int arc, char **arv, char **envp)
{
    t_minishell *shell;
    
    (void)arv;
    (void)arc;
    shell = init_shell(envp);
    if (!shell)
    {
        printf("ERROR:%s \n", "fail allocation of shell");
        exit(1);
    }
    while (1)
    {
        shell->name = readline("👾Minihell> ");
        // if (!shell->name)
        //     free_and_exit(shell);
        if (shell->name[0] == '\0' || is_all_whitespace(shell->name))
        {
            free(shell->name);
            continue;
        }
        add_history(shell->name);
        if (split(shell) == 1)
            exit(1);
        //print(shell.cmd_list);
        exec_builtin(shell, (*(shell->cmd_list))->cmd_line);
        // free_minishell(shell);
        // free_array(shell.envps);
        // free_cmd(*(shell.cmd_list));
        // shell.cmd_list = NULL;
        // get_path_cmd(shell, shell.envps, (*shell.cmd_list).cmd_line);
        // new_prompt(shell);
        // free(shell->name);
        if (shell->cmd_list)
        {
            free_cmd_Aaa(*shell->cmd_list);
            free(shell->cmd_list);
            shell->cmd_list = NULL;
        }
        if (shell->token_space)
        {
            free_array(shell->token_space);
            shell->token_space = NULL;
        }
    }
    // free_minishell(shell);
    free(shell);
    create_free_env_list(*(shell->env_list));
    //free_cmd_Aaa(*shell->cmd_list);
    free(shell->last_arg);
    //     }
    // free_and_exit(&shell);
    return (0);
}

int is_all_whitespace(const char *str)
{
    while (*str)
    {
        if (!ft_isspace(*str))
            return 0;
        str++;
    }
    return 1;
}

int ft_isspace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n'
        || c == '\v' || c == '\f' || c == '\r');
}

// void    new_prompt(t_minishell *shell)
// {
//     if (*(shell->cmd_list))
//         free_cmd(*(shell->cmd_list));
//     *(shell->cmd_list) = NULL;
// }