/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:21:11 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/11 00:55:57 by mmilliot         ###   ########.fr       */
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

void	handle_fork(t_data *data, int *cmd_process,
		int *nbr_of_fork, bool is_builtin)
{
	int	status;

	data->pids[++(*nbr_of_fork)] = fork();
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
		if (*cmd_process > 0)
			close(data->old_read_pipe);
		if (*cmd_process < data->part_of_line - 1)
			close(data->current_pipe[1]);
	}
}

/*
	EXEC_BUILD_OR_CMD = Function for exec a builtin if the token is a builtin
						exec other cmd if the token is not a builtin.
	In the case of a Heredoc, exec_heredoc before the rest of execution.
	In the case of a builtin, setup the redirections, and exec the builtin.
	In the case of an other command, create a child process, setup the
	redirections in the child, and exec the command with execve.
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
			dup2(data->stdin_backup, STDIN_FILENO);
			dup2(data->stdout_backup, STDOUT_FILENO);
		}
	}
	else
		handle_fork(data, cmd_process, nbr_of_fork, false);
}
