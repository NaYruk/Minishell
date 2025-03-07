/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:04:52 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/07 15:31:35 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_command(t_data *data, t_token *current)
{
	(void)current;
	find_path_env(data);
	/* int i = -1;
	while (data->exec->path_cmd_env[++i] != NULL)
	{
		printf("%s\n", data->exec->path_cmd_env[i]);
	} */
	data->exec->cmd_path = find_command_path(data, current);
	//printf("%s\n", data->exec->cmd_path);
	find_command_args(data, current);
	int i = -1;
	while (data->exec->arg[++i] != NULL)
	{
		printf("%s\n", data->exec->arg[i]);
	}
	return (0);
}