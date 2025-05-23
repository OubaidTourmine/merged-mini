/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:46:49 by outourmi          #+#    #+#             */
/*   Updated: 2025/05/23 17:35:48 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **get_envi(t_data *data, char *path)
{
    int i = 0;
    while(data->env[i])
    {
        if(strncmp(path, data->env[i], ft_strlen_ft(path)) == 0)
        {
            return(ft_split(data->env[i] + 5, ':'));
        }
        i++;
    }
    return(0);
}

char *cmd_found(char **path)
{
    int i = 0;
    while(path[i])
    {
        if (access(path[i], X_OK) == 0)
            return(path[i]);
        i++;
    }
    return(NULL);
}

void do_child(t_data *data, char *cmd_path)
{
    int pid;
    char **args;
    pid = fork();
    if(pid == 0)
    {
        if (data->commands->args[1]) {
            args = malloc(sizeof(char*) * 3);
            if (!args) {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }
            args[0] = data->commands->args[0];
            args[1] = data->commands->args[1];
            args[2] = NULL;
        }
        else
        {
            args = malloc(sizeof(char*) * 2);
            if (!args) {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }
            args[0] = data->commands->args[0];
            args[1] = NULL;
        }
        execve(cmd_path, args, data->env);
        perror("execve");
        free(args);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
        wait(NULL);
    else
        perror("fork");
}

int execution(t_data *data)
{
    int i = 0;
    char **path = get_envi(data, "PATH");
    while(path[i])
    {
        path[i] = ft_strjoin_ft(path[i], "/");
        i++;
    }
    i = 0;
    while(path[i])
    {
        path[i] = ft_strjoin_ft(path[i], data->commands->args[0]);
        i++;
    }
    char *cmd_path;
    cmd_path = cmd_found(path);
    if(cmd_path == NULL)
        printf("%s; command not found\n", data->commands->args[0]);
    else
        do_child(data, cmd_path);
    return(0);
}