/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:12:19 by melvin            #+#    #+#             */
/*   Updated: 2025/04/23 07:25:08 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	ft_check_env - Checks if an environment variable matches a give name. 
	
	This function compares the given name with the environment variable. 
	It determines if the variable exists and whether it has a value:
	- 0 if the variable does not match
	- 1 if the variable exists without a value. 
	- 2 if the variable exists with a value. 
*/

static int	ft_check_env(char *env, char *name, int len, int *available)
{
	if (ft_strncmp(env, name, len) == 0 && env[len] == '\0')
	{
		if (available)
			*available = 1;
		return (1);
	}
	if (ft_strncmp(env, name, len) == 0 && env[len] == '=')
	{
		if (available)
			*available = 2;
		return (2);
	}
	return (0);
}

/* 
	ft_getenv - Retrieves the value of an environment variable. 
	
	This function searches for the specified environment variable in 
	'data->env'.
	If the variable exists and has a value, it returns a pointer to the value. 
	If the variable exists without a value, it returns NULL. 
*/

char	*ft_getenv(t_data *data, char *name, int *available)
{
	int		i;
	int		len;
	int		find_var;

	if (available)
		*available = 0;
	if (!data || !data->env)
		return (NULL);
	i = 0;
	len = ft_strlen(name);
	while (data->env[i])
	{
		find_var = ft_check_env(data->env[i], name, len, available);
		if (find_var == 1)
			return (NULL);
		if (find_var == 2)
			return (data->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

/* 
	ft_create_env_variable - Creates a new environment variable string. 

	This function allocates memory and creates a new environment variable
	string in the format 'name=value'. 
	If 'value' is NULL, the string will only contain 'name='. 
*/

static char	*ft_create_env_variable(char *name, char *value)
{
	char	*result;
	int		len_total;

	len_total = ft_strlen(name) + 1;
	if (value)
		len_total += ft_strlen(value);
	len_total += 1;
	result = malloc(sizeof(char) * len_total);
	if (!result)
		return (NULL);
	ft_strncpy(result, name, ft_strlen(name));
	result[ft_strlen(name)] = '=';
	if (value)
		ft_strncpy(result + ft_strlen(name) + 1, value, ft_strlen(value));
	result[len_total - 1] = '\0';
	return (result);
}

/* 
	ft_update_env - Updates an environment variable.

	This function searches for the environment variable in 'data->env'.
	If the variable exists, it updates its value.
	If it does not exists, the function does nothing.
*/

void	ft_update_env(t_data *data, char *name, char *value)
{
	int	i;

	i = 0;
	if (!data || !data->env)
		return ;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0
			&& (data->env[i][ft_strlen(name)] == '='
			|| data->env[i][ft_strlen(name)] == '\0'))
		{
			if (value)
			{
				free(data->env[i]);
				data->env[i] = ft_create_env_variable(name, value);
				return ;
			}
		}
		i++;
	}
	return ;
}

/* 
	ft_delete_env - Deletes an environment variable.

	This function searches for the environment variable in 'data->env'.
	If the variable exists, it removes it from the environment and shifts
	the remaining variables to fill the gap.
*/

void	ft_delete_env(t_data *data, char *name)
{
	int	i;
	int	j;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0
			&& (data->env[i][ft_strlen(name)] == '='
			|| data->env[i][ft_strlen(name)] == '\0'))
		{
			free (data->env[i]);
			j = i;
			while (data->env[j + 1])
			{
				data->env[j] = data->env[j + 1];
				j++;
			}
			data->env[j] = NULL;
			return ;
		}
		i++;
	}
}
