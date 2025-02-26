/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:39:36 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/26 15:14:38 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function for initialize all data need in Minishell 
	Malloc the struct data,
	Call the init_garbage_collector function for init the garbage collector
	All Malloc need to be follow by add_new_g_b_node function for adding
	of the malloc adress in the garbage collector.
*/

t_data	*init_all(void)
{
	t_data *data;
	
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Error with a malloc\n");
		exit(EXIT_FAILURE);
	}
	init_garbage_collector(data);
	data->nbr_pipes = 0;
	data->prompt = NULL;
	data->split = NULL;
	return (data);
}