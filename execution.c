/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:46:49 by outourmi          #+#    #+#             */
/*   Updated: 2025/05/22 21:14:12 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char **get_envi(t_inf *inf, char *path)
{
    int i = 0;
    while(inf->env[i])
    {
        if(strncmp(path, inf->env[i], ft_strlen_ft(path)) == 0)
        {
            return(ft_split(inf->env[i] + 5, ':'));
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

void do_child(t_inf *inf, char *cmd_path)
{
    int pid;
    char **args;
    pid = fork();
    if(pid == 0)
    {
        if (inf->arg) {
            args = malloc(sizeof(char*) * 3);
            if (!args) {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }
            args[0] = inf->command;
            args[1] = inf->arg;
            args[2] = NULL;
        }
        else
        {
            args = malloc(sizeof(char*) * 2);
            if (!args) {
                perror("malloc failed");
                exit(EXIT_FAILURE);
            }
            args[0] = inf->command;
            args[1] = NULL;
        }
        execve(cmd_path, args, inf->env);
        perror("execve");
        free(args);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
        wait(NULL);
    else
        perror("fork");
}

int execution(t_inf *inf)
{
    int i = 0;
    char **path = get_envi(inf, "PATH");
    while(path[i])
    {
        path[i] = ft_strjoin_ft(path[i], "/");
        i++;
    }
    i = 0;
    while(path[i])
    {
        path[i] = ft_strjoin_ft(path[i], inf->command);
        i++;
    }
    char *cmd_path;
    cmd_path = cmd_found(path);
    if(cmd_path == NULL)
        printf("%s; command not found\n", inf->command);
    else
        do_child(inf, cmd_path);
    return(0);
}