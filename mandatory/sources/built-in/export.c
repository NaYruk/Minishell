/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:55:04 by melvin            #+#    #+#             */
/*   Updated: 2025/04/02 01:35:04 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_realloc_env(t_data *data, size_t new_size)
{
	char	**new_env;
	size_t	old_size;
	size_t	i;
	
	old_size = 0;
	while (data->env && data->env[old_size])
		old_size++;
/* 	if (new_size == 0)
		free_env(data); */
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

void	ft_extract_name_value(char *str, char **name, char **value)
{
	char	*plus_equal_pos;
	char	*equal_pos;

	*name = NULL;
	*value = NULL;
	equal_pos = NULL;
	plus_equal_pos = NULL;
	plus_equal_pos = ft_strnstr(str, "+=", ft_strlen(str));
	if (plus_equal_pos)
	{
		*name = ft_strndup(str, plus_equal_pos - str);
		*value = ft_strdup(plus_equal_pos + 2);
	}
	else
	{
		equal_pos = ft_strchr(str, '=');
		if (equal_pos)
		{
			*name = ft_strndup(str, equal_pos - str);
			*value = ft_strdup(equal_pos + 1);
		}
		else
		{
			*name = ft_strdup(str);
			*value = NULL;
		}
	}
}

static int	ft_add_env(t_data *data, char *str)
{
	char	*name;
	char	*value;
	char	*new_value;
	char	*existing_value;
	int		available;

	name = NULL;
	value = NULL;
	new_value = NULL;
	existing_value = NULL;
	available = 0;

	ft_extract_name_value(str, &name, &value);
	if (ft_verif_name(name) == 1)
		return (free (name), free (value), 1);
	existing_value = ft_getenv(data, name, &available);
	if (available == 0)
		ft_add_new_env(data, name, value);
	else if (available == 1 || available == 2)
	{
		if (ft_strnstr(str, "+=", ft_strlen(str)))
		{
			if (existing_value)
				new_value = ft_strjoin(existing_value, value);
			else
				new_value = ft_strdup(value);
			if (!new_value)
				malloc_error(data);
			ft_update_env(data, name, new_value);
			free (new_value);
		}
		else
			ft_update_env(data, name, value);
	}
	return (free(name), free (value), 0);
}

void	ft_process_export(t_data *data, int *error, char **args_cmd)
{
	int		i;
	char	*env_var;

	i = 0;
	env_var = NULL;
	if (!args_cmd[i] || !args_cmd[i + 1])
		return;
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

int	ft_export(t_data *data, char **args_cmd)
{
	char 	**tmp;
	int		error;

	error = 0;
	if (args_cmd[1])
	{
		ft_process_export(data, &error, args_cmd);
		if (error == 1)
			return (data->exit_status = 1, EXIT_SUCCESS);
		return (data->exit_status = 0, EXIT_SUCCESS);
	}
	tmp = ft_duplicate_env(data);
	ft_display_env(tmp);
	ft_free_tmp(tmp);
	return (data->exit_status = 0, EXIT_SUCCESS);
}

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

void	ft_error_name(char *str)
{
	ft_putstr_fd("'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

int	ft_verif_name(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = search_egal(str);
	if (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	else
		return (ft_error_name(str), 1);
	while (str[i] && (i < j || j == -1))
	{
		if (ft_isalnum(str[i]) || str[i] == '_' || (str[i] == '+' && str[i + 1] == '='))
			i++;
		else
			return (ft_error_name(str), 1);
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

