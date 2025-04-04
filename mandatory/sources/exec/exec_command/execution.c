/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:49:08 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/04 16:20:03 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	get_next_pipe_or_null(t_token **current)
{
	while (*current && (*current)->token != PIPE)
		*current = (*current)->next;
	if (*current && (*current)->token == PIPE)
		return (true);
	return (false);
}

void	setup_pipe(t_data *data, int cmd_process)
{
	if (cmd_process < data->nbr_of_command - 1)
	{
		if (pipe(data->current_pipe) == -1)
			malloc_error(data);
	}
	return ;
}

int	handle_execution(t_data *data, t_token **current,
				int *cmd_process, int *nbr_of_fork)
{
	if (set_exec_struct(data, current) == -1)
	{
		if (get_next_pipe_or_null(current) == false)
		{
			free_exec_struct(data);
			return (-1);
		}
		else if (*cmd_process < data->nbr_of_command - 1)
			close(data->current_pipe[1]);
	}
	else if (data->nbr_of_command > 0 && data->exec->arg_cmd)	
		exec_build_or_cmd(data, cmd_process, nbr_of_fork);
	return (0);
}

void	exec(t_data *data, t_token *current)
{
	int	cmd_process;
	int	nbr_of_fork;

	cmd_process = 0;
	nbr_of_fork = -1;
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);
	while (current != NULL)
	{
		setup_pipe(data, cmd_process);
		if (handle_execution(data, &current, &cmd_process, &nbr_of_fork) == -1)
			break ;
		data->old_read_pipe = data->current_pipe[0];
		cmd_process++;
		free_exec_struct(data);
	}
	wait_all(data, nbr_of_fork);
	close (data->stdin_backup);
	close (data->stdout_backup);
}

void	execution(t_data *data)
{
	t_token	*current;

	current = data->lst_token;
	set_nbr_of_commands(data);
	init_exec(data);
	get_pids(data);
	exec(data, current);
}
