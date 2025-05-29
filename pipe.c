/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:36:17 by outourmi          #+#    #+#             */
/*   Updated: 2025/05/29 14:20:44 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pipe(t_data *data)
{
    int i = 0;
    t_command *current = data->commands;
    if (!current)
        return (0);
    while (current)
    {
        if (current->args && current->args[0])
        {
            // printf("Command %d: %s\n", i, current->args[0]);
            current = current->next;
        }
        i++;
    }
    return (i);
}

// int fds[2];
//     if (flag)
//     {
//         if (pipe(fds) == -1)
//         //handle error
//             return ;
//         do_dup(fds, );
//     }



//     void first_child()
// {
    
// }

// void do_dup(int fds, int flag)
// {
//     if(flag == 0)
//     {
//         first_child();
//     }
    
// }
