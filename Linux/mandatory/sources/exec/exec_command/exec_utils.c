/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:04:47 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/09 22:54:38 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* SET_NBR_OF_COMMAND = Function for find the nbr of command in token */

void	set_nbr_of_commands(t_data *data)
{
	t_token	*current;

	current = data->lst_token;
	data->nbr_of_command = 0;
	data->part_of_line = 1;
	while (current != NULL)
	{
		if (current->token == CMD)
			data->nbr_of_command++;
		if (current->token == PIPE)
			data->part_of_line++;
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

void	free_redir_nodes(t_data *data)
{
	t_exec_redir	*tmp;

	tmp = NULL;
	while (data->exec->t_exec_redir != NULL)
	{
		tmp = data->exec->t_exec_redir->next;
		free(data->exec->t_exec_redir);
		data->exec->t_exec_redir = tmp;
	}
	return ;
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
	{
		free(data->exec->cmd_path);
		data->exec->cmd_path = NULL;
	}
	if (data->exec->t_exec_redir)
	{
		free_redir_nodes(data);
		data->exec->t_exec_redir = NULL;
	}
}
