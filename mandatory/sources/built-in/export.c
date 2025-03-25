/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:55:04 by melvin            #+#    #+#             */
/*   Updated: 2025/03/25 15:58:23 by mcotonea         ###   ########.fr       */
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
	char	*name;
	char	*value;
	char	*equal_pos;

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
	if (!name || (equal_pos && !value))
		malloc_error(data);
	if (ft_verif_name(name) == 1)
	{
		free(name);
		free (value);
		return (1);
	}
	if (ft_getenv(data, name))
		ft_update_env(data, name, value);
	else
		ft_add_new_env(data, name, value);
	free (name);
	free (value);
	return (0);
}

void	ft_process_export(t_data *data, int *error)
{
	t_token *tmp;
	char	*env_var;

	env_var = NULL;
	tmp = data->lst_token;
	if (!tmp || !tmp->next)
		return;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->token == ARG)
		{
			env_var = tmp->line;
			if (ft_verif_name(env_var) == 1)
			{
				*error = 1;
				tmp = tmp->next;
				continue ;
			}
			ft_add_env(data, tmp->line);
		}
		tmp = tmp->next;
	}
	return ;
}

char	**ft_duplicate_env(t_data *data)
{
	size_t 	i;
	size_t 	env_size;
	char	**tmp;

	env_size = 0;
	while (data->env && data->env[env_size])
		env_size++;
	tmp = malloc(sizeof(char *) * (env_size + 1));
	if (!tmp)
		malloc_error(data);
	i = 0;
	while (i < env_size)
	{
		tmp[i] = ft_strdup(data->env[i]);
		if (!tmp[i])
			malloc_error(data);
		i++;	
	}
	tmp[i] = NULL;
	return (tmp);
}

void	ft_sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_display_env(char **tmp)
{
	int		i;
	char	*equal_pos;

	ft_sort_env(tmp);
	i = 0;
	while (tmp[i])
	{
		equal_pos = ft_strchr(tmp[i], '=');
		if (equal_pos)
		{
			*equal_pos = '\0';
			printf("declare -x %s=\"%s\"\n", tmp[i], equal_pos + 1);
			*equal_pos = '=';
		}
		else
			printf("declare -x %s=\n", tmp[i]);
		i++;
	}
}

void	ft_free_tmp(char **tmp)
{
	int i;

	i = 0;
	while (tmp[i])
	{
		free (tmp[i]);
		i++;
	}
	free (tmp);
	return ;
}

int	ft_export(t_data *data)
{
	char 	**tmp;
	int		error;

	error = 0;
	if (data->lst_token->next)
	{
		ft_process_export(data, &error);
		if (error == 1)
			return (data->exit_status = 1, EXIT_SUCCESS);
		return (data->exit_status = 0, EXIT_SUCCESS);
	}
	tmp = ft_duplicate_env(data);
	ft_display_env(tmp);
	ft_free_tmp(tmp);
	return (data->exit_status = 0, EXIT_SUCCESS);
}

int	ft_verif_name(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
		i++;
	else
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '=')
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
 