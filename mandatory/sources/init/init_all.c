/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:39:36 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/26 13:37:39 by mmilliot         ###   ########.fr       */
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
	data->prompt = NULL;
	data->env = NULL;
	data->lst_token = NULL;
	data->exec = NULL;
	data->operator = false;
	data->exit_status = 0;
	data->nbr_of_command = 0;
	data->stdin_backup = 0;
	data->stdout_backup = 0;
	data->classic_or_hd_expand = 0;
	data->simple_q = false;
	data->double_q = false;
	data->quotes_char = '\0';
	data->pids = NULL;
	data->pipes = NULL;
	copy_envp(envp, data);
	return (data);
}
