/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:49:08 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/23 02:54:47 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** get_next_pipe_or_null:
** - This function searches for the next pipe token (`|`) in the token list.
** - Advances the `current` pointer to the next pipe or the end of the list.
** - Returns `true` if a pipe token is found, otherwise returns `false`.
*/

bool	get_next_pipe_or_null(t_token **current)
{
	while (*current && (*current)->token != PIPE)
		*current = (*current)->next;
	if (*current && (*current)->token == PIPE)
		return (true);
	return (false);
}

/*
** setup_pipe:
** - This function sets up a pipe for inter-process communication.
** - Creates a new pipe if the current command
**		is not the last one in the pipeline.
** - Handles errors during pipe creation by calling the `malloc_error` function
*/

void	setup_pipe(t_data *data, int cmd_process)
{
	if (cmd_process < data->part_of_line - 1)
	{
		if (pipe(data->current_pipe) == -1)
			malloc_error(data);
	}
	return ;
}

/*
** handle_execution:
** - This function manages the execution of a single command or built-in.
** - Sets up the execution structure for the current command.
** - Handles cases where the command is invalid or not executable.
** - Executes the command or built-in and manages the pipeline connections.
** - Closes the write end of the current pipe if no further command are execute
** - Returns 0 on success or -1 if an error occurs during execution.
*/

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
		if ((data->part_of_line - 1) > 0 && data->old_read_pipe != -1)
			close(data->old_read_pipe);
	}
	else if (data->nbr_of_command > 0 && data->exec->arg_cmd)
		exec_build_or_cmd(data, cmd_process, nbr_of_fork);
	if (*cmd_process < data->part_of_line - 1)
		close(data->current_pipe[1]);
	return (0);
}

/*
** exec:
** - This function handles the execution of commands
**		and manages the pipeline setup.
** - Iterates through the token list, setting up pipes
**		and executing commands or built-ins.
** - Handles heredoc execution and restores standard
**		input/output after execution.
** - Waits for all child processes to finish and cleans up resources.
*/

void	exec(t_data *data, t_token *current)
{
	int	cmd_process;
	int	nbr_of_fork;
	int	status;

	cmd_process = 0;
	nbr_of_fork = -1;
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);
	status = exec_heredoc(data);
	while (current != NULL && status != -1)
	{
		setup_pipe(data, cmd_process);
		if (handle_execution(data, &current, &cmd_process, &nbr_of_fork) == -1)
			break ;
		if (cmd_process < data->part_of_line - 1)
			data->old_read_pipe = data->current_pipe[0];
		cmd_process++;
		free_exec_struct(data);
	}
	wait_all(data, nbr_of_fork);
	if (data->part_of_line > 1)
		close(data->old_read_pipe);
	close_heredoc_fd(data);
	close (data->stdin_backup);
	close (data->stdout_backup);
}

/*
** execution:
** - This function orchestrates the execution of commands in the shell.
** - Initializes necessary structures and variables for command execution.
** - Iterates through the token list, setting up pipe and handling each command
** - Manages the execution of built-in commands or external programs.
** - Waits for all child processes to finish and restores standard input/output
*/

void	execution(t_data *data)
{
	t_token	*current;

	data->old_read_pipe = -1;
	current = data->lst_token;
	set_nbr_of_commands(data);
	init_exec(data);
	get_pids(data);
	exec(data, current);
}
