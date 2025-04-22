/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:50:41 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/11 00:44:16 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
Function for add a new node in the front of garbage collector chained list 
*/

void	add_front_node(t_garb_c **lst, t_garb_c *new_node)
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

void	add_g_c_node(t_data *data, t_garb_c **g_c, void **memory, bool is_arr)
{
	t_garb_c	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_garb_c));
	if (!new_node)
	{
		perror("Error with a malloc\n");
		free_garbage(data);
		exit(EXIT_FAILURE);
	}
	new_node->memory = memory;
	new_node->next = NULL;
	if (is_arr == true)
		new_node->is_array = true;
	else
		new_node->is_array = false;
	add_front_node(g_c, new_node);
	return ;
}

static void	free_array(t_data *data)
{
	char	**array;
	int		i;

	if (!data->g_c->memory)
		return ;
	array = (char **)data->g_c->memory;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	data->g_c->memory = NULL;
}

/* 
	Function for free all memory malloc in the programm :
	- If the memory is an array, the fonction free the contain
		and free the array.
*/

void	free_garbage(t_data *data)
{
	t_garb_c	*temp;

	while (data->g_c != NULL)
	{
		temp = data->g_c->next;
		if (data->g_c->memory)
		{
			if (data->g_c->is_array == true)
				free_array(data);
			else
			{
				free(data->g_c->memory);
				data->g_c->memory = NULL;
			}
		}
		free(data->g_c);
		data->g_c = temp;
	}
	data->g_c = NULL;
	ft_free_env(data->env);
	if (data)
		free(data);
}
