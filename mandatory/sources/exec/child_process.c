/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:09:46 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/28 02:14:05 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

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
		close_pipes(data);
		exit(EXIT_FAILURE);
	}
	close_pipes(data);
	i = 3;
	while (i < 1024)
		close(i++);
	if (!data->exec->cmd_path)
	{
		ft_putstr_fd(data->exec->arg_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (access(data->exec->cmd_path, X_OK) == -1)
	{
		ft_putstr_fd(data->exec->cmd_path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	if (execve(data->exec->cmd_path, data->exec->arg_cmd, data->env) == -1)
	{
		perror("Execve :");
		exit(EXIT_FAILURE);
	}
	exit(0);
}
