/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesco <francesco@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 02:34:29 by francesco         #+#    #+#             */
/*   Updated: 2024/01/29 05:18:07 by francesco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_arg(char *arg)
{
    int i;

    i = 0;
    while (arg[i] && arg[i] != '=')
        i++;
    if (!arg[i])
        return (0);
    if (i == 0)
        return (0);
    if (arg[0] == '=')
        return (0);
    return (1);
}

char *extract_name(char *arg)
{
    int i;
    char    *name;

    i = 0;
    while (arg[i] && arg[i] != '=')
        i++;
    name = ft_substr(arg, 0, i);
    return (name);
    
}

char    *extract_value(char *arg)
{
    int     i;
    char    *value;

    i = 0;
    value = NULL;
    while (arg[i] && arg[i] != '=')
        i++;
    value = ft_substr(arg, i + 1, ft_strlen(arg));
    if (ft_strlen(value) == 0)
    {
        free(value);
        return (NULL);
    }
    return (value);
}

int check_if_env(t_dlist *env, char *name)
{
    t_dlist *temp;
    t_env   *data;

    temp = env;
    while (temp != NULL)
    {
        data = env->data;
        if (ft_strncmp(name, data->name, ft_strlen(name + 1)))
            return (1);
        temp = temp->next;
    }
    return (0);
}

int add_to_env(t_dlist *env, char *name, char *value)
{
    t_dlist *new;
    t_env   *data;

    new = malloc(sizeof(*new) * 1);
    if (!new)
        return (err("minishell: malloc error", ERR_MALLOC));
    data = malloc(sizeof(*data) * 1);
    if (!data)
    {
        free(new);
        return(err("minishell: malloc error", ERR_MALLOC));
    }
    data->name = name;
    data->value = value;
    new->data = data;
    ft_dl_add_back(&env, new);
    return (SUCCESS);
}

int trust_the_process(t_dlist *env, char *name, char *value)
{
    t_dlist *temp;
    t_env   *data;

    temp = env;
    while (temp != NULL)
    {
        data = temp->data;
        if (ft_strncmp(name, data->name, ft_strlen(name) + 1) == 0)
        {
            printf("ok\n");
            if (data->value)
                free(data->value);
            data->value = value;
            return (SUCCESS);
        }
        temp = temp->next;
    }
    printf("ok\n");
    if (!add_to_env(env, name, value))
        return (ERR_MALLOC);
    return (SUCCESS);
}

int ft_export(t_exec_cmd *cmd)
{
    int         i;
    t_dlist     *env;
    char        *name;
    char        *value;
    
    env = get_ms()->env;
    i = 1;
    if (cmd->cmd->argc < 2)
        return (0);
   while (i < cmd->cmd->argc)
   {
        if (check_arg(cmd->cmd->argv[i]))
        {
            name = extract_name(cmd->cmd->argv[i]);
            printf("%s\n", name);
            value = extract_value(cmd->cmd->argv[i]);
            trust_the_process(env, name, value);
        }
        i++;
   }
   return (1);
}