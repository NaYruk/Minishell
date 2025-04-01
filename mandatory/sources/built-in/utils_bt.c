/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:12:19 by melvin            #+#    #+#             */
/*   Updated: 2025/04/02 01:28:50 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_env(char *env, char *name, int	len, int *available)
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
	Function that obtains a value of an environnement variable if it exists
	It looks like the getenv function.
	name is the name of the variable without '='.
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


static char	*ft_create_env_variable(char *name, char *value)
{
	char 	*result;
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
	Function that adds or modifies an environnement variable
	It looks like the setenv function.
	name is the name of the variable without '='.
*/

void	ft_update_env(t_data *data, char *name, char *value)
{
	int	i;

	i = 0;
	if (!data || !data->env)
		return ;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0)
		{
			if (value)
			{
				free(data->env[i]);
				data->env[i] = ft_create_env_variable(name,value);
				return ;
			}
		}
		i++;
	}
	return ;
}

/* 
	Function that delete an environnement variable.
	name is the name of the variable without '='.
*/

void	ft_delete_env(t_data *data, char *name)
{
	int	i;
	int	j;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0)
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
