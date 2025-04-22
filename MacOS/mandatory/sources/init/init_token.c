/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:31:54 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/26 14:08:18 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Function for free each node in token chained list */

void	free_token(t_data *data)
{
	t_token	*tmp;

	tmp = NULL;
	while (data->lst_token != NULL)
	{
		tmp = data->lst_token->next;
		free(data->lst_token->line);
		free(data->lst_token);
		data->lst_token = tmp;
	}
	return ;
}

/* Function for get the last node of the chained list*/

t_token	*last_node(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
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
	new->prev = end_list;
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

void	add_new_token(t_data *data, t_token **lst, char *line)
{
	t_token	*new;

	new = NULL;
	new = malloc(sizeof(t_token));
	if (!new)
		malloc_error(data);
	new->line = line;
	new->next = NULL;
	new->prev = NULL;
	new->token = -1;
	if (data->quotes_char == SIMPLE_QUOTES)
		new->quote_char = SIMPLE_QUOTES;
	else if (data->quotes_char == DOUBLE_QUOTES)
		new->quote_char = DOUBLE_QUOTES;
	else
		new->quote_char = '\0';
	add_node_back(lst, new);
	return ;
}
