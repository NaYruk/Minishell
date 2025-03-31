/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:55:04 by melvin            #+#    #+#             */
/*   Updated: 2025/03/31 21:53:39 by mcotonea         ###   ########.fr       */
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

static void	ft_add_new_env(t_data *data, char *name, char *value)
{
	int		old_size;
	char	*new_entry;
	size_t 	size;
	size_t 	name_len;
	size_t	value_len;

	old_size = 0;
	while (data->env && data->env[old_size])
		old_size++;
	ft_realloc_env(data, old_size + 1);
	name_len = ft_strlen(name);
	if (value)
		value_len = ft_strlen(value);
	else 
		value_len = 0;
	size = name_len + 1;
	if (value_len > 0)
		size += value_len + 1;
	new_entry = malloc(sizeof(char) * size);
	if (!new_entry)
		malloc_error(data);
	ft_strncpy(new_entry, name, name_len);
	new_entry[name_len] = '\0';
	if (value)
	{
		new_entry[name_len] = '=';
		ft_strncpy(new_entry + name_len + 1, value, value_len);
		new_entry[name_len + value_len + 1] = '\0';
	}
	data->env[old_size] = new_entry;
	data->env[old_size + 1] = NULL;
}

static int	ft_add_env(t_data *data, char *env)
{
	char	*name = NULL;
	char	*value = NULL;
	char	*plus_equal_pos = NULL;
	char	*equal_pos = NULL;
	char	*old_value = NULL;
	char	*new_value = NULL;
	int		available = 0;

	plus_equal_pos = ft_strnstr(env, "+=", ft_strlen(env));
	if (plus_equal_pos)
	{
		name = ft_strndup(env, plus_equal_pos - env);
		value = ft_strdup(plus_equal_pos + 2);
	}
	else
	{
		equal_pos = ft_strchr(env, '=');
		if (!equal_pos)
		{
			name = ft_strdup(env);
			value = NULL;
		}
		else
		{
			name = ft_strndup(env, equal_pos - env);
			value = ft_strdup(equal_pos + 1);
		}
	}
	if (!name || (equal_pos && !value))
		malloc_error(data);
	if (ft_verif_name(name) == 1)
	{
		free(name);
		free (value);
		return (1);
	}
	if (ft_getenv(data, name, &available) || available == 1)
	{
		if (plus_equal_pos)
		{
			old_value = ft_getenv(data, name, NULL);
			if (!old_value)
				old_value = "";
			if (!value)
				value = "";
			new_value = ft_strjoin(old_value, value);
			if (!new_value)
				malloc_error(data);
			ft_update_env(data, name, new_value);
			free (new_value);
		}
		else
			ft_update_env(data, name, value);
	}
	else
		ft_add_new_env(data, name, value);
	free (name);
	free (value);
	return (0);
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
	return (0);
}

int	ft_verif_name(char *str)
{
	int	i;
	int	j;
	
	j = search_egal(str);
	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	else
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	while (str[i] && i < j)
	{
		if (ft_isalnum(str[i]) || str[i] == '_' || (str[i] == '+' && str[i + 1] == '='))
			i++;
		else
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (1);
		}
	}
	while (str[i] && i >= j && j != 0)
	{		
		if (ft_isascii(str[i]))
			i++;
		else
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}
