/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:55:04 by melvin            #+#    #+#             */
/*   Updated: 2025/04/03 18:39:30 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	ft_verif_name(char *str)
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

static int	ft_add_env(t_data *data, char *str)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	ft_extract_name_value(str, &name, &value);
	if (ft_verif_name(name) == 1)
		return (free (name), free (value), 1);
	process_existing_env(data, str, name, value);
	return (free(name), free (value), 0);
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
	ft_free_tmp(tmp);
	return (data->exit_status = 0, EXIT_SUCCESS);
}
