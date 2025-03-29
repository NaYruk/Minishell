/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:04:47 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/29 07:49:23 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* SET_NBR_OF_COMMAND = Function for find the nbr of command in token */

void	set_nbr_of_commands(t_data *data)
{
	t_token	*current;

	current = data->lst_token;
	data->nbr_of_command = 0;
	while (current != NULL)
	{
		if (current->token == CMD)
			data->nbr_of_command++;
		current = current->next;
	}
}

/* 
	GET_PIDS_AND_PIPES =
		malloc pipes and pids based on the number of commands found 
*/

void	get_pids(t_data *data)
{
	if (data->nbr_of_command > 0)
	{
		data->pids = malloc(sizeof(pid_t) * data->nbr_of_command);
		if (!data->pids)
			malloc_error(data);
		add_g_c_node(data, &data->g_c, (void **)data->pids, false);
	}
}

/* FREE_EXEC_STRUCT = function for free the exec struct for the next command. */

void	free_exec_struct(t_data *data)
{
	int	i;

	i = -1;
	if (data->exec->arg_cmd)
	{
		while (data->exec->arg_cmd[++i] != NULL)
			free(data->exec->arg_cmd[i]);
		free(data->exec->arg_cmd);
		data->exec->arg_cmd = NULL;
	}
	if (data->exec->cmd_path)
		free(data->exec->cmd_path);
	if (data->exec->infile != NULL)
		free(data->exec->infile);
	if (data->exec->outfile != NULL)
		free(data->exec->outfile);
	if (data->exec->append != NULL)
		free(data->exec->append);
	if (data->exec->heredoc != NULL)
		free(data->exec->heredoc);
	data->exec->heredoc = NULL;
	data->exec->infile = NULL;
	data->exec->outfile = NULL;
	data->exec->cmd_path = NULL;
	data->exec->arg_cmd = NULL;
	data->exec->append = NULL;
	if (data->exec->last_heredoc_fd != -1)
		close(data->exec->last_heredoc_fd);
}
