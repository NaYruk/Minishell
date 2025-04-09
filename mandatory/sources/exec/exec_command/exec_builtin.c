/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:32:33 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/09 13:00:52 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/* 
	This function executes the builtin commands when
	they are on the command line.
*/

int	exec_builtin(t_data *data, char **args_cmd, int cmd_process)
{
	if (setup_redirection(data, cmd_process) == -1)
		return (-1);
	if (ft_strcmp(args_cmd[0], "pwd") == 0)
		return (data->exit_status = ft_pwd(data), data->exit_status);
	else if (ft_strcmp(args_cmd[0], "cd") == 0)
		return (data->exit_status = ft_cd(data, args_cmd), data->exit_status);
	else if (ft_strcmp(args_cmd[0], "exit") == 0)
		return (data->exit_status = ft_exit(data, args_cmd),
			data->exit_status);
	else if (ft_strcmp(args_cmd[0], "env") == 0)
		return (data->exit_status = ft_env(data), data->exit_status);
	else if (ft_strcmp(args_cmd[0], "echo") == 0)
		return (data->exit_status = ft_echo(data, args_cmd),
			data->exit_status);
	else if (ft_strcmp(args_cmd[0], "unset") == 0)
		return (data->exit_status = ft_unset(data, args_cmd),
			data->exit_status);
	else if (ft_strcmp(args_cmd[0], "export") == 0)
		return (data->exit_status = ft_export(data, args_cmd),
			data->exit_status);
	if (cmd_process < data->part_of_line - 1)
		close(data->current_pipe[1]);
	return (0);
}
