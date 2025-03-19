/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:02:12 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/19 07:48:04 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function to free the old data->env.
*/

static void	free_env(t_data *data)
{
	int	i;

	i = 0;
	if (!data->env)
		return ;
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free (data->env);
	data->env = NULL;
	return ;
}

/* 
	Function similar to realloc.
	Resizes an array of array to a larger size.
*/

void	ft_realloc_env(t_data *data, size_t new_size)
{
	char	**new_env;
	size_t	old_size;
	size_t	i;
	
	old_size = 0;
	while (data->env && data->env[old_size])
		old_size++;
	
	if (new_size == 0)
		free_env(data);
	new_env = malloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		malloc_error(data);
	i = 0;
	while (i < old_size && i < new_size)
	{
		new_env[i] = data->env[i];
		i++;
	}
	while (i < old_size)
	{
		free(data->env[i]);
		i++;
	}
	while (i <= new_size)
	{
		new_env[i] = NULL;
		i++;
	}
	free (data->env);
	data->env = new_env;
}

/* 
	Function used to add a new environnement variable.
	The new variable can be composed of name only (NAME=) 
	or name+value(NAME=VALUE).
	The presence of an '=' sign is mandatory.
*/

static void	ft_add_env(t_data *data, char *env)
{
	size_t	old_size;
	char	*equal_pos;
	char	*name;
	char	*value;
	char	*result;
	
	equal_pos = ft_strchr(env, '=');
	if (!equal_pos)
		return ;
	name = ft_strndup(env, equal_pos - env);
	value = ft_strdup(equal_pos + 1);
	if (ft_getenv(data, name) != NULL)
	{
		free (name);
		free (value);
		return ;
	}
	if (!name || !value)
		malloc_error(data);
	old_size = 0;
	while (data->env && data->env[old_size])
		old_size++;
	ft_realloc_env(data, old_size + 1);
	result = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 2));
	if (!result)
		malloc_error(data);
	ft_strncpy(result, name, ft_strlen(name) + 1);
	result[ft_strlen(name)] = '=';
	ft_strncpy(result + ft_strlen(name) + 1, value, ft_strlen(value) + 1);
	data->env[old_size] = result;
	data->env[old_size + 1] = NULL;
	free (name);
	free (value);
}

int	ft_export(t_data *data)
{
	t_token *tmp;

	tmp = data->lst_token;
	if (!tmp || !tmp->next)
		return (EXIT_FAILURE);
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->token == ARG)
			ft_add_env(data, tmp->line);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
