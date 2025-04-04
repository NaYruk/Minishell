/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:04:12 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/04 19:35:55 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

void	execute_heredoc(t_data *data, t_token *current)
{
	t_token *current_start;

	current_start = current;
	while (current != NULL)
	{
		if (current->prev && current->prev->token == HEREDOC
				&& current->token == ARG)
			exec_heredoc(data, current);
		current = current->next;
	}
	return ;
}
int	set_exec_struct(t_data *data, t_token **current)
{
	data->error_built = -1;
	if ((*current)->token == PIPE)
		*current = (*current)->next;
	execute_heredoc(data, *current);
	while (*current != NULL)
	{
		if ((*current)->token == PIPE)
			break ;
		if (args_and_cmd(data, current) == -1)
			return (-1);
		set_heredoc(data, *current);
		if (set_append(data, *current) == -1)
			return (-1);
		if (set_outfile(data, *current) == -1)
			return (-1);
		if (set_infile(data, *current) == -1)
			return (-1);
		*current = (*current)->next;
	}
	return (0);
}
