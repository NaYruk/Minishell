/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:09:46 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/29 08:26:55 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(t_data *data)
{
	free_exec_struct(data);
	free_token(data);
	free(data->prompt);
	free_garbage(data);
}

/* 
	CHILD_PROCESS = Function execute in a fork.
	
	In the case of an other command, create a child process, setup the
	redirections in the child, and exec the command with execve.
	EXECVE : if cmd = ls : cmd_path = /bin/ls.
			 if cmd = ls -la : arg_cmd = [ls] [-la] [NULL]
			 env = variable of environnement
*/

int	child_process(t_data *data, int i)
{
	close(data->stdin_backup);
	close(data->stdout_backup);
	if (setup_redirection(data, i, false) == -1)
		exit(EXIT_FAILURE);
	if (!data->exec->cmd_path)
	{
		ft_putstr_fd(data->exec->arg_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_all(data);
		exit(127);
	}
	if (access(data->exec->cmd_path, X_OK) == -1)
	{
		ft_putstr_fd(data->exec->cmd_path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_all(data);
		exit(126);
	}
	if (execve(data->exec->cmd_path, data->exec->arg_cmd, data->env) == -1)
	{
		perror("Execve :");
		exit(EXIT_FAILURE);
	}
	exit(0);
}
