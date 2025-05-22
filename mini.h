/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:13:39 by outourmi          #+#    #+#             */
/*   Updated: 2025/05/22 21:12:29 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../yazide-oubaid-minishell-yazid/minishell.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_inf
{
	char	**env;
	char	**export;
	char	*command;
	char	*arg;
	char	*flag;
	char 	*pipe;
	char	less;
	char	great;
}			t_inf;

int 		execution(t_inf *inf);
char		**ft_split(char const *s, char c);
int			ft_strcmp_ft(char *s1, char *s2);
int			ft_strncmp_ft(char *s1, char *s2, size_t n);
int			get_export(t_inf *inf);
size_t		ft_strlen_ft(char *s);
char		*ft_strjoin_ft(char *s1, char *s2);
char		*ft_strdup_ft(char *src);
char		*ft_substr_ft(char *s, unsigned int start, size_t len);
void		free_array(char **ptr);
int			func_export(t_inf *inf);

#endif