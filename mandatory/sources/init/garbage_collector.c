/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:50:41 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/26 15:04:56 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function for initialize the garbage collector.
	Garbage collector is a chained list.
	She stock all memory malloc in the programm.
	This is the simplest method for free all malloc.
	In the programm for free all we need just to call the function :
	free_garbage(t_data *data)
*/

void	init_garbage_collector(t_data *data)
{
	data->g_c = malloc(sizeof(t_garbage_collector));
	if (!data->g_c)
	{
		free(data);
		perror("Error with a malloc\n");
		exit(EXIT_FAILURE);
	}
	data->g_c->memory = NULL;
	data->g_c->next = NULL;
	return ;
}

/* 
Function for add a new node in the front of garbage collector chained list 
*/

void	add_front_node(t_garbage_collector **lst, t_garbage_collector *new_node)
{
	if (!lst || !new_node)
		return ;
	new_node->next = *lst;
	*lst = new_node;
	return ;
}

/* 
	Function for create a new node for the garbage collector :
	data = struct contain all data.
	**g_c = garbage collector struct, need to write &data->g_c in argument.
	**memory = memory malloc cast in a **void. So : (void **)memory.
*/

void	add_new_g_b_node(t_data *data, t_garbage_collector **g_c, void **memory)
{
	t_garbage_collector *new_node;
	
	new_node = NULL;
	new_node = malloc(sizeof(t_garbage_collector));
	if (!new_node)
	{
		perror("Error with a malloc\n");
		free_garbage(data);
		exit(EXIT_FAILURE);
	}
	new_node->memory = memory;
	new_node->next = NULL;
	add_front_node(g_c, new_node);
	return ;
}

/* Function for free all memory malloc in the programm */

void	free_garbage(t_data *data)
{
	t_garbage_collector	*temp;
	
	while (data->g_c != NULL)
	{
		temp = data->g_c->next;
		if (data->g_c->memory)
			free(data->g_c->memory);
		free(data->g_c);
		data->g_c = temp;
	}
	free(data);
}

