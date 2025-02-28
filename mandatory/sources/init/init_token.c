/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:31:54 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/28 15:17:39 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Function for get the size of the chained list */

static int	size_list(t_token *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/* Function for get the last node of the chained list*/

static t_token	*last_node(t_token *lst)
{
	int	i;
	
	if (!lst)
		return (0);
	i = size_list(lst);
	while (i > 1)
	{
		lst = lst->next;
		i--;
	}
	return (lst);
}	

/* Function for add a node in the back of the chained list */

static void	add_node_back(t_token **lst, t_token *new)
{
	t_token	*end_list;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	end_list = last_node(*lst);
	end_list->next = new;
	return ;
}

/*
	Function for add a new_token node 
	This chained list contain the prompt line
	after the tokenization process.
	each node contain :
	- the line of the token
	- the value of the token
	- a pointer in the next token
*/

void	add_new_token_node(t_data *data, t_token **lst, char *line)
{
	t_token	*new;
	
	new = NULL;
	new = malloc(sizeof(t_token));
	if (!new)
	{
		perror("Error with a malloc\n");
		free_garbage(data);
		exit(EXIT_FAILURE);
	}
	new->line = line;
	new->next = NULL;
	new->token = -1;
	add_g_c_node(data, &data->g_c, (void **)new, false);
	add_g_c_node(data, &data->g_c, (void **)line, false);
	add_node_back(lst, new);
	return ;
}
