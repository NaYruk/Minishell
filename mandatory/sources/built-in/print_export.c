/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:51:52 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/17 01:43:19 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	ft_duplicate_env - Duplicates the environment variables.
*/

char	**ft_duplicate_env(t_data *data)
{
	size_t	i;
	size_t	env_size;
	char	**tmp;

	env_size = 0;
	while (data->env && data->env[env_size])
		env_size++;
	tmp = malloc(sizeof(char *) * (env_size + 1));
	if (!tmp)
		malloc_error(data);
	i = 0;
	while (data->env[i] && i < env_size)
	{
		tmp[i] = ft_strdup(data->env[i]);
		if (!tmp[i])
			malloc_error(data);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

/* 
	ft_sort_env - Sorts the environment variables alphabetically. 
*/

static void	ft_sort_env(char **env)
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

/* 
	ft_display_env - Displays the environment variables. 
*/

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
			printf("declare -x %s\n", tmp[i]);
		i++;
	}
}
