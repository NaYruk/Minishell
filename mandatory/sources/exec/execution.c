/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:27:33 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/07 13:54:42 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function for init the exec structure :
	She contain :
	- arg : Arguments of the cmd, give to execve
	- cmd_path : path of the executable file.
	- path_cmd_env : char **, 
		he contain all path possible for a command exectable.
*/

void	init_exec_struct(t_data *data)
{
	data->exec = malloc(sizeof(t_exec));
	if (!data->exec)
		malloc_error(data);
	data->exec->arg = NULL;
	data->exec->cmd_path = NULL;
	data->exec->path_cmd_env = NULL;
	data->exec->pid = -1;
	return ;	
}

/* Function for free the exec struct */

void	free_exec_struct(t_data *data)
{
	int	i;

	if (data->exec->arg != NULL)
	{
		i = -1;
		while (data->exec->arg[++i] != NULL)
			free(data->exec->arg[i]);
		free(data->exec->arg);
		data->exec->arg = NULL;
	}
	if (data->exec->cmd_path != NULL)
		free(data->exec->cmd_path);
	if (data->exec->path_cmd_env != NULL)
	{
		i = -1;
		while (data->exec->path_cmd_env[++i] != NULL)
			free(data->exec->path_cmd_env[i]);
		free(data->exec->path_cmd_env);
		data->exec->path_cmd_env = NULL;
	}
	free(data->exec);
}

int	execution(t_data *data)
{
	t_token *current;

	current = data->lst_token;
	init_exec_struct(data);
	while (current != NULL)
	{
		if (current->token == CMD)
		{
			if (exec_builtin(data) == 0)
			{
				execute_command(data, current);
			}
		}
		current = current->next;
	}
	free_exec_struct(data);
	return (0);
}
