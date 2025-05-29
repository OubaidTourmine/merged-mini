/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:46:49 by outourmi          #+#    #+#             */
/*   Updated: 2025/05/29 16:29:46 by outourmi         ###   ########.fr       */
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

int do_child(t_data *data, char *cmd_path, int flag)
{
    int pid;
    char **args;
    if(flag == 0)
    {
        pid = fork();
        if(pid == 0)
        {
            if (data->commands->args[1])
            {
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
    else
    {
        int i = 0;
        t_command *current = data->commands;
        if (!current)
            return (0);
        while (current)
        {
            if (current->args && current->args[0])
            {
                current = current->next;
            }
            i++;
        }
        int fd[i - 1][2];
        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        while(i != 0)
        {
            
        }
    }
    return(0);
}

int execution(t_data *data ,int flag)
{
    int i = 0;
    char **path = get_envi(data, "PATH");
    if(data->commands->next)
        flag = 1;
    else
        flag = 0;
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
        do_child(data, cmd_path, flag);
    return(0);
}