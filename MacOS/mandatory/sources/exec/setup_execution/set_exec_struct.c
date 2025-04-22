/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:04:12 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/19 00:01:12 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** init_exec:
** - This function initializes the execution structure for a command pipeline.
** - Allocates memory for the `t_exec` structure and adds
**		it to the garbage collector.
** - Sets all fields of the execution structure
**		(`arg_cmd`, `cmd_path`, `t_exec_redir`) to NULL.
** - Handles memory allocation errors by calling `malloc_error` if necessary.
*/

void	init_exec(t_data *data)
{
	data->exec = malloc(sizeof(t_exec));
	if (!data->exec)
		malloc_error(data);
	add_g_c_node(data, &data->g_c, (void **)data->exec, false);
	data->exec->arg_cmd = NULL;
	data->exec->cmd_path = NULL;
	data->exec->t_exec_redir = NULL;
}

/*
** args_and_cmd:
** - This function processes the command token and its
**		arguments in the token list.
** - Retrieves the arguments for the command and stores them
**		in the execution structure.
** - Resolves the command path using the `get_cmd_path` function.
** - Returns 0 on success or -1 if an error occurs during argument
**		or path retrieval.
*/

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

/*
** set_exec_struct:
** - This function initializes and populates the execution structure
**		for a command pipeline segment.
** - Skips over pipe tokens and processes the tokens
**		in the current pipeline segment.
** - Handles command arguments, heredocs, and redirections
**		(append, outfile, infile).
** - Calls helper functions to retrieve the command path
**		and set up redirection nodes.
** - Returns 0 on success or -1 if an error occurs during setup.
*/

int	set_exec_struct(t_data *data, t_token **current)
{
	t_token	*cmd;

	cmd = NULL;
	data->error_built = -1;
	if ((*current)->token == PIPE)
		*current = (*current)->next;
	while (*current != NULL)
	{
		if ((*current)->token == PIPE)
			break ;
		if ((*current)->token == CMD)
			cmd = *current;
		set_heredoc(data, *current);
		if (set_append(data, *current) == -1)
			return (-1);
		if (set_outfile(data, *current) == -1)
			return (-1);
		if (set_infile(data, *current) == -1)
			return (-1);
		*current = (*current)->next;
	}
	if (cmd && args_and_cmd(data, &cmd) == -1)
		return (-1);
	return (0);
}
