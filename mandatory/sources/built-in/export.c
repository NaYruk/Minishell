/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:39:10 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/17 01:41:24 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	ft_add_new_env - Adds a new environment variable.

	This functions creates a new environment variable by combining
	the name and value, reallocates the array to include the new variable.
*/

void	ft_add_new_env(t_data *data, char *name, char *value)
{
	int		old_size;
	int		len_total;
	char	*new_entry;

	new_entry = NULL;
	old_size = 0;
	while (data->env && data->env[old_size])
		old_size++;
	ft_realloc_env(data, old_size + 1);
	len_total = (ft_strlen(name) + 1) + (ft_strlen(value) + 1);
	new_entry = malloc(sizeof(char) * len_total);
	if (!new_entry)
		malloc_error(data);
	ft_strcpy(new_entry, name);
	if (value)
	{
		new_entry[ft_strlen(name)] = '=';
		ft_strcpy(new_entry + ft_strlen(name) + 1, value);
	}
	data->env[old_size] = new_entry;
	data->env[old_size + 1] = NULL;
}

/* 
	ft_handle_append - Handles appending a value to an existing env variable
*/

static void	ft_handle_append(t_data *data, t_env *env)
{
	if (env->existing_value)
		env->new_value = ft_strjoin(env->existing_value, env->value);
	else
		env->new_value = ft_strdup(env->value);
	if (!env->new_value)
		malloc_error(data);
	ft_update_env(data, env->name, env->new_value);
	free (env->new_value);
}

/*  
	ft_add_env - Adds or updates an environment variable

	This function extracts the name and value from the input string, verifies
	the name, and either adds a new variable, appends to an existing or updates
	its value.
	If the name is invalid, it returns an error. 
*/

static int	ft_add_env(t_data *data, char *str)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(t_env));
	ft_extract_name_value(str, &env.name, &env.value);
	if (ft_verif_name(env.name) == 1)
		return (free(env.name), free(env.value), 1);
	env.existing_value = ft_getenv(data, env.name, &env.available);
	if (env.available == 0)
		ft_add_new_env(data, env.name, env.value);
	else if (ft_strnstr(str, "+=", ft_strlen(str)))
		ft_handle_append(data, &env);
	else
		ft_update_env(data, env.name, env.value);
	return (free(env.name), free (env.value), 0);
}

/* 
	ft_process_export - Processes the arguments of the 'export' command. 

	This function iterates trhough the arguments of the 'export' command,
	validates each variable name, and adds or updates the env variable.
	If an invalid name is encountered, it sets the error flag. 
*/

static void	ft_process_export(t_data *data, int *error, char **args_cmd)
{
	int		i;
	char	*env_var;

	i = 0;
	env_var = NULL;
	if (!args_cmd[i] || !args_cmd[i + 1])
		return ;
	i++;
	while (args_cmd[i] && ft_strcmp(args_cmd[i], "|") != 0)
	{
		env_var = args_cmd[i];
		if (ft_verif_name(env_var) == 1)
		{
			*error = 1;
			i++;
			continue ;
		}
		ft_add_env(data, args_cmd[i]);
		i++;
	}
	return ;
}

/* 
	ft_export - Implements the 'export' command. 

	This function handles the logic for the 'export':
	- If no arguments, it displays the current env variables. 
	- If arguments are provided,it processes each one to add or updates var. 
	- If an invalid variable name is encoutered, it sets the exit status to 1. 
*/

int	ft_export(t_data *data, char **args_cmd)
{
	char	**tmp;
	int		error;

	error = 0;
	if (args_cmd[1])
	{
		ft_process_export(data, &error, args_cmd);
		if (error == 1)
			return (data->exit_status = 1, EXIT_FAILURE);
		return (data->exit_status = 0, EXIT_SUCCESS);
	}
	tmp = ft_duplicate_env(data);
	ft_display_env(tmp);
	ft_free_env(tmp);
	return (data->exit_status = 0, EXIT_SUCCESS);
}
