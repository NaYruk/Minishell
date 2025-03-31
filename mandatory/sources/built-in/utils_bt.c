/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:12:19 by melvin            #+#    #+#             */
/*   Updated: 2025/03/31 20:43:04 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function that obtains a value of an environnement variable if it exists
	It looks like the getenv function.
	name is the name of the variable without '='.
*/

char	*ft_getenv(t_data *data, char *name, int *available)
{
	int		i;
	int		len;

	i = 0;
	if (available)
		*available = 0;
	len = ft_strlen(name);
	if (!data || !data->env)
		return (NULL);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, len) == 0 && data->env[i][len] == '\0')
		{
			if (available)
				*available = 1;
			return (NULL);	
		}
		else if (ft_strncmp(data->env[i], name, len) == 0
			&& data->env[i][len] == '=')
			{
				if (available)
					*available = 2;
				return (data->env[i] + len + 1);
			}
		i++;
	}
	return (NULL);
}

/* 
	Function that adds or modifies an environnement variable
	It looks like the setenv function.
	name is the name of the variable without '='.
*/

void	ft_update_env(t_data *data, char *name, char *value)
{
	int	i;
	int	len_total;

	i = 0;
	len_total = ft_strlen(name) + ft_strlen(value);
	if (!data || !data->env)
		return ;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0)
		{
			if (value)
			{
				free(data->env[i]);
				data->env[i] = malloc(sizeof(char) * len_total + 2);
				if (!data->env[i])
					return ;
				ft_strncpy(data->env[i], name, ft_strlen(name) + 1);
				data->env[i][ft_strlen(name)] = '=';
				ft_strncpy(data->env[i] + ft_strlen(name) + 1,
					value, ft_strlen(value) + 1);
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

	// if (ft_getenv(data, name) == NULL)
	// 	return ;
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
