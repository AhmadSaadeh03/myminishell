/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:29:12 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/12 19:19:37 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishill.h"

void print_env_list(t_env **env_list)
{
    t_env *temp = *env_list;
    if (!temp)
    {
        printf("Environment list is empty.\n");
        return;
    }
    printf("Environment list:\n");
    while (temp)
    {
        printf("%s=%s\n", temp->env_name, temp->value);
        temp = temp->next;
    }
}
void expand(t_minishell *shell,t_env **env_list)
{
    t_node *temp;
    char *new;
    //t_env *env_list;

    //env_list = copy_env_to_list();
   //env_list =NULL;
    temp = shell->token_list;

    while (temp)
    {
        if (ft_strcmp(temp->node, "export") == 0 && temp->next)
        {
                temp = temp->next;
               handle_export(temp->node,env_list);
        }
        if (ft_strcmp(temp->node, "unset") == 0 && temp->next)
        {
                temp = temp->next;
                my_unsetenv(env_list,temp->node);            
        }
        if (temp->cmd_type == TOKEN_ARG)
        {
            // Step 1: Handle environment variables
            new = handle_env(temp->node, *env_list);
            if (!new)
                return;
            // Step 2: Remove quotes
            char *final = ft_trim_quotes(new);
            free(new); // Free the intermediate string
            if (!final)
                return;
                
            // Update the node with the final processed string
            free(temp->node);
            temp->node = final;
            if (temp->node)
                printf("%s\n", temp->node);
        }

        temp = temp->next;
    }
}

char    *my_getenv(t_env *env_list, char *name)
{
        t_env   *temp;
        temp = env_list;
        while (temp)
        {
                if (ft_strcmp(temp->env_name, name) == 0)
                {
                        return (temp->value);
                }
                temp = temp->next;
        }
        return (NULL);
}

void my_setenv(t_env **env_list, char *name, char *value)
{
    t_env *temp = *env_list;
    // Check if the variable already exists
    while (temp)
    {
        if (ft_strcmp(temp->env_name, name) == 0)
        {
            printf("Updating existing variable: %s=%s\n", name, value);
            free(temp->value);
            temp->value = ft_strdup(value);
            return;
        }
        temp = temp->next;
    }
    printf("Adding new variable: %s=%s\n", name, value);
    t_env *new_node = malloc(sizeof(t_env));
    if (!new_node)
    {
        printf("Memory allocation failed for new_node\n");
        return;
    }
    new_node->env_name = ft_strdup(name);
    new_node->value = ft_strdup(value);
    new_node->next = *env_list;
    *env_list = new_node;
}
void my_unsetenv(t_env **env_list, char *name)
{
    t_env *temp = *env_list;
    t_env *prev = NULL;
    while (temp)
    {
        if (ft_strcmp(temp->env_name, name) == 0)
        {
            if (prev == NULL)
                *env_list = temp->next;
            else
                prev->next = temp->next;
            free(temp->env_name);
            free(temp->value);
            free(temp);
            printf("Removed variable: %s\n", name);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Variable not found: %s\n", name);
}