/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:04:52 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/07 18:00:14 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(t_data *data, int index_pid)
{
	data->exec->pid[index_pid] = fork();
	if (data->exec->pid[index_pid] == 0)
	{
		if (execve(data->exec->cmd_path, data->exec->arg, data->env))
		{
			perror("ERROR");
			exit(EXIT_FAILURE);
		}
	}
	return ;
}

int	execute_command(t_data *data, t_token *current)
{
	static int	index_pid = 0;
	
	find_path_env(data);
	data->exec->cmd_path = find_command_path(data, current);
	find_command_args(data, current);
	exec(data, index_pid);
	index_pid++;
	return (0);
}