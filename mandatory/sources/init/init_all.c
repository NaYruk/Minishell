/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:39:36 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/09 17:10:42 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Function for copy the envp in a char ** variable */

void	copy_envp(char **envp, t_data *data)
{
	int	line_number;
	int	i;

	line_number = 0;
	while (envp[line_number] != NULL)
		line_number++;
	data->env = malloc(sizeof(char *) * (line_number + 1));
	if (!data->env)
		malloc_error(data);
	i = -1;
	while (envp[++i] != NULL)
		data->env[i] = ft_strdup(envp[i]);
	data->env[i] = NULL;
}

void	update_shlvl(t_data *data)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = ft_getenv(data, "SHLVL", NULL);
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str);
		if (shlvl < 0)
			shlvl = 0;
	}
	else
		shlvl = 0;
	shlvl++;
	ft_update_env(data, "SHLVL", ft_itoa(shlvl));
}

/* 
	Function for initialize all data need in Minishell 
	Malloc the struct data,
	Call the init_garbage_collector function for init the garbage collector
	All Malloc need to be follow by add_new_g_b_node function for adding
	of the malloc adress in the garbage collector.
*/

t_data	*init_all(char **envp)
{
	t_data	*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Error with a malloc\n");
		exit(EXIT_FAILURE);
	}
	init_garbage_collector(data);
	ft_memset(data, 0, sizeof(t_data));
	data->old_read_pipe = -1;
	data->current_pipe[0] = -1;
	data->current_pipe[1] = -1;
	copy_envp(envp, data);
	update_shlvl(data);
	return (data);
}
