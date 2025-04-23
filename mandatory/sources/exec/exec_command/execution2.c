/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:21:11 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/23 02:56:57 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* Function for detected if a builtin is present */

int	exec_build(char *line)
{
	if (ft_strcmp(line, "pwd") == 0)
		return (1);
	else if (ft_strcmp(line, "cd") == 0)
		return (1);
	else if (ft_strcmp(line, "exit") == 0)
		return (1);
	else if (ft_strcmp(line, "env") == 0)
		return (1);
	else if (ft_strcmp(line, "echo") == 0)
		return (1);
	else if (ft_strcmp(line, "unset") == 0)
		return (1);
	else if (ft_strcmp(line, "export") == 0)
		return (1);
	return (0);
}

/*
** handle_fork:
** - This function handles the creation of a child process using `fork`.
** - If the command is a built-in, it executes the built-in
**		in the child process and exits with its status.
** - If the command is not a built-in, it delegates execution
**		to the `child_process` function.
** - Manages the closing of pipes for the parent process
**		to ensure proper pipeline behavior.
*/

void	handle_fork(t_data *data, int *cmd_process,
		int *nbr_of_fork, bool is_builtin)
{
	int	status;

	data->pids[++(*nbr_of_fork)] = fork();
	if (data->pids[*nbr_of_fork] == -1)
		error(data, "Fork");
	if (data->pids[*nbr_of_fork] == 0)
	{
		if (is_builtin == true)
		{
			status = exec_builtin(data, data->exec->arg_cmd, *cmd_process);
			free_all(data);
			exit(status);
		}
		else
			child_process(data, *cmd_process);
	}
	else
	{
		if (*cmd_process > 0 && (data->part_of_line - 2) > 0)
			close(data->old_read_pipe);
	}
}

/*
** exec_build_or_cmd:
** - This function determines whether to execute a built-in
**		command or an external program.
** - If the command is a built-in, it executes it directly or forks
**		a process if part of a pipeline.
** - If the command is not a built-in, it forks a process
**		to execute the external program.
** - Manages input/output redirection and restores standard
**		input/output when necessary.
*/

void	exec_build_or_cmd(t_data *data, int *cmd_process, int *nbr_of_fork)
{
	if (exec_build(data->exec->arg_cmd[0]))
	{
		if (data->part_of_line > 1)
			handle_fork(data, cmd_process, nbr_of_fork, true);
		else if (exec_builtin(data, data->exec->arg_cmd, *cmd_process) == -1)
			data->error_built = 1;
		if (data->part_of_line == 1)
		{
			if (dup2(data->stdin_backup, STDIN_FILENO) == -1)
				error(data, "dup2");
			if (dup2(data->stdout_backup, STDOUT_FILENO) == -1)
				error(data, "dup2");
		}
	}
	else
		handle_fork(data, cmd_process, nbr_of_fork, false);
	if (data->heredoc_in_pipe == 1)
		data->hd_index++;
	data->heredoc_in_pipe = 0;
}
