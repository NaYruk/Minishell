/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 03:05:05 by melvin            #+#    #+#             */
/*   Updated: 2025/04/17 02:04:23 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	search_egal - Searches the '=' character in a string. 
*/

static int	search_egal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/* 
	verif_name - Verifies the validity of an environment variable name.
*/

int	ft_verif_name(char *str)
{
	int	i;
	int	j;

	i = 1;
	j = search_egal(str);
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (ft_error_name(str), 1);
	while (str[i] && (i < j || j == -1))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_'
			&& !(str[i] == '+' && str[i + 1] == '='))
			return (ft_error_name(str), 1);
		i++;
	}
	if (j != -1)
	{
		while (str[i])
		{
			if (ft_isascii(str[i]))
				i++;
			else
				return (ft_error_name(str), 1);
		}
	}
	return (0);
}

/* 
	ft_extract_name_value - Extracts the name and value from an 
								environment variable string.
	
	This function parses the given string to separate the name and value of an
	environment variable. 
	If the string contains `+=`, it handles appending logic.
	If the string contains only a name, the value is set to NULL.
*/

void	ft_extract_name_value(char *str, char **name, char **value)
{
	char	*pos;

	*name = NULL;
	*value = NULL;
	pos = NULL;
	pos = ft_strnstr(str, "+=", ft_strlen(str));
	if (pos)
	{
		*name = ft_strndup(str, pos - str);
		*value = ft_strdup(pos + 2);
	}
	else
	{
		pos = ft_strchr(str, '=');
		if (pos)
		{
			*name = ft_strndup(str, pos - str);
			*value = ft_strdup(pos + 1);
		}
		else
			*name = ft_strdup(str);
	}
	if (!*name || (pos && !*value))
		malloc_error(NULL);
}

/* 
	ft_realloc_env - Reallocates the environment array to a new size.

	This function reallocates the 'data->env' array to the specified size. 
	It copies the existing environment variables into the new array
	and initializes the remaining slots to NULL. The old array is freed. 
*/

void	ft_realloc_env(t_data *data, size_t new_size)
{
	char	**new_env;
	size_t	i;

	if (!data || ! data->env)
		return ;
	new_env = malloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		malloc_error(data);
	i = 0;
	while (data->env[i] && i < new_size)
	{
		new_env[i] = data->env[i];
		i++;
	}
	while (i < new_size)
	{
		new_env[i] = NULL;
		i++;
	}
	free (data->env);
	data->env = new_env;
}
