/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:04:47 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/11 03:53:51 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	set_nbr_of_commands(t_data *data)
{
	t_token *current;

	current = data->lst_token;
	while (current != NULL)
	{
		if (current->token == CMD)
			data->nbr_of_command++;
		current = current->next;
	}
}

void	get_pids_and_pipes(t_data *data, pid_t **pids, int (**pipes)[2])
{
	//int	i;

	//i = -1;
	if (data->nbr_of_command > 0)
	{
		*pids = malloc(sizeof(pid_t) * data->nbr_of_command);
		if (!(*pids))
			malloc_error(data);
		*pipes = malloc(sizeof(int[2]) * (data->nbr_of_command - 1));
		if (!(*pipes))
		{
			free((*pids));
			malloc_error(data);
		}
		/*while (++i < data->nbr_of_command - 1)
		{ 
			if (pipe(*pipes[i]) < 0)
			{
				perror("Pipe_failed\n");
				error(data);
			}
		}*/
	}
}

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
		free(data->exec->cmd_path);
	data->exec->infile = NULL;
	data->exec->outfile = NULL;
	data->exec->cmd_path = NULL;
	data->exec->arg_cmd = NULL;
}

void	init_exec(t_data *data)
{
	data->exec = malloc(sizeof(t_exec));
	if (!data->exec)
		malloc_error(data);
	data->exec->arg_cmd = NULL;
	data->exec->cmd_path = NULL;
	data->exec->infile = NULL;
	data->exec->outfile = NULL;
}
