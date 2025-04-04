/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:04:12 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/04 14:29:37 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

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

void	add_new_redir_node(t_data *data, t_exec_redir **lst, char *line, int type)
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

void	init_exec(t_data *data)
{
	data->exec = malloc(sizeof(t_exec));
	if (!data->exec)
		malloc_error(data);
	add_g_c_node(data, &data->g_c, (void **)data->exec, false);
	data->exec->arg_cmd = NULL;
	data->exec->cmd_path = NULL;
	data->exec->t_exec_redir = NULL;
	data->exec->last_heredoc_fd = -1;
}

int	args_and_cmd(t_data *data, t_token **current)
{
	if ((*current)->token == CMD)
	{
		get_args_cmd(data, *current);
		if (get_cmd_path(data, current) == -1)
			return (-1);
	}
	return (0);
}

int	set_exec_struct(t_data *data, t_token **current)
{
	data->error_built = -1;
	if ((*current)->token == PIPE)
		*current = (*current)->next;
	while (*current != NULL)
	{
		if ((*current)->token == PIPE)
			break ;
		if (args_and_cmd(data, current) == -1)
			return (-1);
		if (set_append(data, *current) == -1)
			return (-1);
		if (set_outfile(data, *current) == -1)
			return (-1);
		if (set_infile_heredoc(data, *current) == -1)
			return (-1);
		*current = (*current)->next;
	}
	return (0);
}
