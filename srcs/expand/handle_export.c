/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:51:55 by fghanem           #+#    #+#             */
/*   Updated: 2025/04/12 19:11:46 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishill.h"

void handle_export(char *str, t_env **env_list)
{
    int i = 0;
    int j = 0;
    char *before_equal = ft_strdup("");
    char *after_equal = ft_strdup("");
    while (str[i] && str[i] != '=')
    {
        before_equal[j] = str[i];
        i++;
        j++;
    }
    before_equal[j] = '\0';
    i++;
    j = 0;
    while (str[i])
    {
        after_equal[j] = str[i];
        i++;
        j++;
    } 
    after_equal[j] = '\0';
    if (after_equal && before_equal)
        my_setenv(env_list, before_equal, after_equal);

    free(after_equal);
    free(before_equal);
}