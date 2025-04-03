/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:09:17 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/03 18:35:00 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_realloc_env(t_data *data, size_t new_size)
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

static void	ft_add_new_env(t_data *data, char *name, char *value)
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
		pos = ft_strchr(str, pos - str);
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

static void	add_to_exis_env(t_data *data, char *name, char *value, char *exis)
{
	char	*new_value;

	new_value = NULL;
	if (exis)
		new_value = ft_strjoin(exis, value);
	else
		new_value = ft_strdup(value);
	if (!new_value)
		malloc_error(data);
	ft_update_env(data, name, new_value);
	free (new_value);
}

void	process_existing_env(t_data *data, char *str, char *name, char *value)
{
	char	*existing_value;
	int		available;

	existing_value = ft_getenv(data, name, &available);
	if (available == 0)
		ft_add_new_env(data, name, value);
	else if (ft_strnstr(str, "+=", ft_strlen(str)))
		add_to_exis_env(data, name, value, existing_value);
	else
		ft_update_env(data, name, value);
}
