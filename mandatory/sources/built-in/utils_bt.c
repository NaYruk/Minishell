/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:12:19 by melvin            #+#    #+#             */
/*   Updated: 2025/03/11 01:24:52 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function that obtains a value of an environnement variable if it exists
	It looks like the getenv function.
	name is the name of the variable without '='.
*/

char	*ft_getenv(t_data *data, char *name)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	if (!data || !data->env)
		return (NULL);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, len) == 0
			&& data->env[i][len] == '=')
			return (data->env[i] + len + 1);
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
	int i;
	int	len_total;

	i = 0;
	len_total = ft_strlen(name) + ft_strlen(value);
	if (!data || !data->env)
		return ;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0
			&& data->env[i][ft_strlen(name)] == '=')
		{
			free(data->env[i]);
			data->env[i] = malloc(sizeof(char) * len_total + 2);
			if (!data->env[i])
				return ;
			ft_strlcpy(data->env[i], name, ft_strlen(name) + 1);
			data->env[i][ft_strlen(name)] = '=';
			ft_strlcpy(data->env[i] + ft_strlen(name) + 1, value, ft_strlen(value) + 1);
			return ;
		}
		i++;
	}
	return ;
}

/* static void	free_env(t_data *data)
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
} */

/* void	ft_realloc_env(t_data *data, size_t new_size)
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
	add_g_c_node(data, &data->g_c, (void **)data->env, true);
}

void	ft_add_env(t_data *data, char *name, char *value)
{
	size_t	old_size;
	char	*new_var;

	if (ft_getenv(data, name) != NULL)
		return ;
	old_size = 0;
	while (data->env && data->env[old_size])
		old_size++;
	ft_realloc_env(data, old_size + 1);
	new_var = malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(value) + 2));
	if (!new_var)
		malloc_error(data);
	ft_strlcpy(new_var, name, ft_strlen(name) + 1);
	new_var[ft_strlen(name)] = '=';
	ft_strlcpy(new_var + ft_strlen(name) + 1, value, ft_strlen(value) + 1);
	data->env[old_size] = new_var;
	data->env[old_size + 1] = NULL; 
}
 */