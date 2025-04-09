/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:09:46 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/09 13:01:36 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	if (setup_redirection(data, i) == -1)
	{
		free_all(data);
		exit(EXIT_FAILURE);
	}
	setup_signals_execution();
	if (execve(data->exec->cmd_path, data->exec->arg_cmd, data->env) == -1)
	{
		perror("Execve :");
		exit(EXIT_FAILURE);
	}
	exit(0);
}
