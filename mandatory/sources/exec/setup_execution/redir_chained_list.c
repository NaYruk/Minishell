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
