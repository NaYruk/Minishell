/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:55:04 by melvin            #+#    #+#             */
/*   Updated: 2025/04/05 04:42:24 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	ft_handle_append(t_data *data, t_env *env)
{
	if (env->existing_value)
		env->new_value = ft_strjoin(env->existing_value, env->value);
	else
		env->new_value = ft_strdup(env->value);
	if (!env->new_value)
		malloc_error(data);
	ft_update_env(data, env->name, env->new_value);
	free (env->new_value);
}

static int	ft_add_env(t_data *data, char *str)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(t_env));
	ft_extract_name_value(str, &env.name, &env.value);
	if (ft_verif_name(env.name) == 1)
		return (free(env.name), free(env.value), 1);
	env.existing_value = ft_getenv(data, env.name, &env.available);
	if (env.available == 0)
		ft_add_new_env(data, env.name, env.value);
	else if (ft_strnstr(str, "+=", ft_strlen(str)))
		ft_handle_append(data, &env);
	else
		ft_update_env(data, env.name, env.value);
	return (free(env.name), free (env.value), 0);
}

static void	ft_process_export(t_data *data, int *error, char **args_cmd)
{
	int		i;
	char	*env_var;

	i = 0;
	env_var = NULL;
	if (!args_cmd[i] || !args_cmd[i + 1])
		return ;
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
	char	**tmp;
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
	ft_free_env(tmp);
	return (data->exit_status = 0, EXIT_SUCCESS);
}
