/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:39:36 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/23 07:28:34 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** copy_envp:
** - This function copies the environment variables from
**		`envp` into the `data->env` array.
** - Counts the number of environment variables and allocates
**		memory for the `data->env` array.
** - Duplicates each environment variable string and stores it in the new array
** - Ensures proper memory allocation and handles errors if any allocation fail
*/

void	copy_envp(char **envp, t_data *data)
{
	int	line_number;
	int	i;

	line_number = 0;
	while (envp[line_number] != NULL)
		line_number++;
	data->env = malloc(sizeof(char *) * (line_number + 1));
	if (!data->env)
		malloc_error(data);
	i = -1;
	while (envp[++i] != NULL)
		data->env[i] = ft_strdup(envp[i]);
	data->env[i] = NULL;
}

/*
** update_shlvl:
** - This function updates the `SHLVL` (Shell Level) environment variable.
** - Retrieves the current value of `SHLVL` from the environment.
** - Increments the value by 1, ensuring it does not go below 0.
** - Updates the `SHLVL` variable in the environment with the new value.
** - Handles memory allocation and ensures proper error handling.
*/

void	update_shlvl(t_data *data)
{
	char	*shlvl_str;
	int		shlvl;
	int		available;

	shlvl_str = ft_getenv(data, "SHLVL", NULL);
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str);
		if (shlvl < 0)
			shlvl = -1;
	}
	else
		shlvl = 0;
	shlvl++;
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		malloc_error(data);
	ft_getenv(data, "SHLVL", &available);
	if (available == 0)
		ft_add_new_env(data, "SHLVL", shlvl_str);
	else
		ft_update_env(data, "SHLVL", shlvl_str);
	free (shlvl_str);
}

/*
** minienv:
** - This function creates a minimal environment for
**		the shell when no environment is provided.
** - Initializes the `PWD` variable with the current working directory.
** - Sets default values for `SHLVL`, `PATH`, and `OLDPWD`.
** - Allocates memory for the environment variables
**		and ensures proper error handling.
*/

void	minienv(t_data *data)
{
	char	*pwd;

	pwd = NULL;
	data->env = malloc(sizeof(char *) * 5);
	if (!data->env)
		malloc_error(data);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		malloc_error(data);
	data->env[0] = ft_strdup("PWD=");
	data->env[0] = ft_strjoin(data->env[0], pwd);
	data->env[1] = ft_strdup("SHLVL=0");
	data->env[2] = ft_strdup
		("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	data->env[3] = ft_strdup("OLDPWD");
	data->env[4] = NULL;
	free (pwd);
	if (!data->env[0] || !data->env[1] || !data->env[2] || !data->env[3])
		malloc_error(data);
}

/*
** init_all:
** - This function initializes all the data needed for Minishell.
** - Allocates memory for the `t_data` structure and sets
**		its fields to default values.
** - Initializes the garbage collector for memory management.
** - Copies the environment variables into the `data->env` array
**		or creates a minimal environment if none is provided.
** - Updates the `SHLVL` variable to reflect the shell's current level.
** - Returns a pointer to the initialized `t_data` structure.
*/

t_data	*init_all(char **envp)
{
	t_data	*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Error with a malloc\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(data, 0, sizeof(t_data));
	data->old_read_pipe = -1;
	data->current_pipe[0] = -1;
	data->current_pipe[1] = -1;
	if (!envp || !envp[0])
		minienv(data);
	else
		copy_envp(envp, data);
	update_shlvl(data);
	return (data);
}
