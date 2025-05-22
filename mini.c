/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:13:36 by outourmi          #+#    #+#             */
/*   Updated: 2025/05/22 21:18:23 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_x_permession(mode_t mode)
{
	return (mode & S_IXUSR);
}

int	func_pwd(void)
{
	char	*curr_path;

	curr_path = getenv("PWD");
	if (!curr_path)
	{
		perror("getenv failed\n");
		return (1);
	}
	printf("%s\n", curr_path);
	return (0);
}

int	 func_cd(t_inf *inf)
{
	const char	*path;
	struct stat	file_stat;

	if (!inf->arg)
	{
		path = getenv("HOME");
		if (!path)
		{
			perror("getenv failed\n");
			return (1);
		}
		if (chdir(path) == -1)
		{
			perror("chdir failed\n");
			return (1);
		}
		return (0);
	}
	else if (!ft_strcmp_ft(inf->arg, "-"))
	{
		path = getenv("OLDPWD");
		if (!path)
		{
			perror("getenv failed\n");
			return (1);
		}
		if (chdir(path) == -1)
		{
			perror("chdir failed\n");
			return (1);
		}
		return (0);
	}
	else
	{
		path = inf->arg;
		if (!path)
			return (1);
		if (stat(path, &file_stat) == -1)
		{
			perror("stat failed\n");
			return (1);
		}
		if (S_ISDIR(file_stat.st_mode) && check_x_permession(file_stat.st_mode))
		{
			if (chdir(path) == -1)
			{
				perror("chdir failed\n");
				return (1);
			}
			return (0);
		}
	}
	return (1);
}

int	func_echo(t_inf *inf)
{
	printf("%s\n", inf->arg);
	return (0);
}

int	func_env(t_inf *inf)
{
	int	i;

	i = 0;
	while (inf->env[i])
	{
		// if (!inf->env[i  +1])
		// {
		//     break ;
		// }
		printf("%s\n", inf->env[i++]);
	}
	return (0);
}

int	func_exit(t_inf *inf)
{
	(void)inf;
	if (inf->env)
		free_array(inf->env);
	if (inf->export)
		free_array(inf->export);
	free(inf);
	exit(0);
}

size_t	ft_strlen_exp(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		return (0);
	}
	while (s[i] && s[i] != '=')
	{
		i++;
	}
	return (i);
}

int	func_unset(t_inf *inf)
{
	int		i;
	int		var_len;
	int		len_arg;
	char	*var_name;
	int		j;

	i = 0;
	len_arg = ft_strlen_ft(inf->arg);
	while (inf->env[i])
	{
		var_name = inf->env[i];
		var_len = ft_strlen_exp(var_name);
		if (strncmp(var_name, inf->arg, len_arg) == 0 && var_len == len_arg)
		{
			// Free both arrays' entries at this position
			free(inf->env[i]);
			free(inf->export[i]);
			// Shift all subsequent elements
			j = i;
			while (inf->env[j + 1])
			{
				inf->env[j] = inf->env[j + 1];
				inf->export[j] = inf->export[j + 1];
				j++;
			}
			// Null-terminate both arrays at the new end
			inf->env[j] = NULL;
			inf->export[j] = NULL;
			return (0);
		}
		i++;
	}
	return (0);
}

int	func_export(t_inf *inf)
{
	int	i;

	i = 0;
	get_export(inf);
	if (!inf->arg)
	{
		while (inf->export[i + 1])
			printf("%s\n", inf->export[i++]);
	}
	else
	{
		while (inf->env[i])
			i++;
		inf->env[i] = ft_strdup_ft(inf->arg);
		// inf->env[i] = ft_strjoin_ft("declare -x ", inf->arg);
		inf->env[i + 1] = NULL;
		i = 0;
		// while (inf->export[i])
		// {
		//     // if (!inf->export[i  + 2])
		//     // {
		//     //     break ;
		//     // }
		//     // printf("%s\n", inf->export[i++]);
		// }
	}
	return (0);
}

int	builtin(t_inf *inf)
{
	if (ft_strcmp_ft(inf->command, "echo") == 0)
		func_echo(inf);
	else if (ft_strcmp_ft(inf->command, "cd") == 0)
		func_cd(inf);
	else if (ft_strcmp_ft(inf->command, "pwd") == 0)
		func_pwd();
	else if (ft_strcmp_ft(inf->command, "env") == 0)
		func_env(inf);
	else if (ft_strcmp_ft(inf->command, "export") == 0)
		func_export(inf);
	else if (ft_strcmp_ft(inf->command, "unset") == 0)
		func_unset(inf);
	else if (ft_strcmp_ft(inf->command, "exit") == 0)
		func_exit(inf);
	return (0);
}

int	get_env(char **env, t_inf *inf)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	inf->env = malloc((i) * sizeof(char *) + 8);
	if (!inf->env)
		return (1);
	i = 0;
	while (env[i] != NULL)
	{
		inf->env[i] = ft_strdup_ft(env[i]);
		i++;
	}
	inf->env[i] = NULL;
	return (0);
}
int	execution_pars(char **env)
{
	t_inf	*inf;
	char	*line;
	char	*space;

	inf = malloc(sizeof(t_inf));
	get_env(env, inf);
	get_export(inf);
	while (1)
	{
		line = readline("minishell> ");
		space = strchr(line, ' ');
		if (!line)
			break ;
		if (!space)
		{
			inf->command = line;
			inf->arg = NULL;
		}
		else
		{
			*space = '\0';
			inf->command = line;
			inf->arg = space + 1;
		}
		if (inf->command && (
            ft_strcmp_ft(inf->command, "echo") == 0 ||
            ft_strcmp_ft(inf->command, "cd") == 0 ||
            ft_strcmp_ft(inf->command, "pwd") == 0 ||
            ft_strcmp_ft(inf->command, "env") == 0 ||
            ft_strcmp_ft(inf->command, "export") == 0 ||
            ft_strcmp_ft(inf->command, "unset") == 0 ||
            ft_strcmp_ft(inf->command, "exit") == 0))
        {
            builtin(inf);
        }
        else if (inf->command)
        {
            execution(inf);
        }
		free(line);
	}
	if (inf->env)
		free_array(inf->env);
	if (inf->export)
		free_array(inf->export);
	free(inf);
	return (0);
}
