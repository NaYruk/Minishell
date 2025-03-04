/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:39:36 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/04 17:04:51 by mcotonea         ###   ########.fr       */
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
	add_g_c_node(data, &data->g_c, (void **)data->env, true);
	i = -1;
	while (envp[++i] != NULL)
		data->env[i] = ft_strdup(envp[i]);
	data->env[i] = NULL;
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

	(void)envp;
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Error with a malloc\n");
		exit(EXIT_FAILURE);
	}
	init_garbage_collector(data);
	data->prompt = NULL;
	data->env = NULL;
	data->lst_token = NULL;
	data->operator = false;
	data->name_op = NULL;
	copy_envp(envp, data);
	return (data);
}
