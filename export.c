/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:58:22 by outourmi          #+#    #+#             */
/*   Updated: 2025/05/22 21:14:02 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


void	ft_swap(char **export, int i, int j)
{
	char	*tmp;

	tmp = export[i];
	export[i] = export[j];
	export[j] = tmp;
}

void	free_array(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
}

void	sort(char **export)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (export[len])
	{
		len++;
	}
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp_ft(export[j], export[j + 1]) > 0)
				ft_swap(export, j, j + 1);
			j++;
		}
		i++;
	}
}

int	xdeclare(t_inf *inf)
{
	int		i;
	char	*temp;

	i = 0;
	while (inf->export[i])
	{
		temp = inf->export[i];
		inf->export[i] = ft_strjoin_ft("declare -x ", inf->export[i]);
		free(temp);
		i++;
	}
	return (0);
}

int	quote(t_inf *inf)
{
	int		i;
	int		j;
	char	*temp;
	char	*value;
	char	*new_var;
	char	*quoted_value;

	i = 0;
	j = 0;
	while (inf->export[i])
	{
		j = 0;
		while (inf->export[i][j] && inf->export[i][j] != '=')
			j++;
		if (inf->export[i][j] == '=')
		{
			temp = ft_substr_ft(inf->export[i], 0, j + 1);
			value = ft_strjoin_ft("\"", &inf->export[i][j + 1]);
			quoted_value = ft_strjoin_ft(value, "\"");
			new_var = ft_strjoin_ft(temp, quoted_value);
			free(value);
			free(temp);
			free(quoted_value);
			free(inf->export[i]);
			inf->export[i] = new_var;
		}
		i++;
	}
	return (0);
}

int	get_export(t_inf *inf)
{
	int i;

	i = 0;
	while (inf->env[i])
		i++;
	inf->export = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (inf->env[i])
	{
		inf->export[i] = ft_strdup_ft(inf->env[i]);
		i++;
	}
	inf->export[i] = NULL;
	i = 0;
	sort(inf->export);
	xdeclare(inf);
	quote(inf);
	return (0);
}