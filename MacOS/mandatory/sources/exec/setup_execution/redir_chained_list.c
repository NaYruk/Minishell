/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_chained_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:01:23 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/09 17:09:02 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** last_node:
** - This function retrieves the last node in a redirection linked list.
** - Iterates through the list until it reaches the node where `next` is NULL.
** - Returns the last node in the list or NULL if the list is empty.
*/

static t_exec_redir	*last_node(t_exec_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

/*
** add_node_back:
** - This function adds a new node to the end of a redirection linked list.
** - If the list is empty, the new node becomes the first node
**		and its position is set to 1.
** - If the list is not empty, the function finds the last node and appends
**		the new node to it.
** - Updates the `prev` pointer and the position of the new node relative
**		to the list.
** - Ensures proper handling of NULL pointer for both the list and the new node
*/

static void	add_node_back(t_exec_redir **lst, t_exec_redir *new)
{
	t_exec_redir	*end_list;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		new->position = 1;
		return ;
	}
	end_list = last_node(*lst);
	end_list->next = new;
	new->prev = end_list;
	new->position = new->prev->position + 1;
	return ;
}

/*
** add_new_redir_node:
** - This function creates a new redirection node and adds
**		it to the redirection linked list.
** - Allocates memory for a new `t_exec_redir` node and initializes its fields.
** - Sets the `arg` field to the provided line
**		and the `type` field to the redirection type.
** - Adds the new node to the end of the linked list using `add_node_back`.
** - Handles memory allocation errors by calling `malloc_error` if necessary.
*/

void	add_new_redir_node(t_data *data, t_exec_redir **lst,
			char *line, int type)
{
	t_exec_redir	*new;

	new = NULL;
	new = malloc(sizeof(t_exec_redir));
	if (!new)
		malloc_error(data);
	new->arg = line;
	new->type = type;
	new->next = NULL;
	add_node_back(lst, new);
	return ;
}
