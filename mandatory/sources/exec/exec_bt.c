/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:32:33 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/29 06:50:31 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	This function executes the builtin commands when
	they are on the command line.
*/

int	exec_builtin(t_data *data, char **args_cmd, int cmd_process)
{
	if (setup_redirection(data, cmd_process, true) == -1)
		return (-1);
	if (ft_strcmp(args_cmd[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(args_cmd[0], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(args_cmd[0], "exit") == 0)
		ft_exit(data, args_cmd);
	else if (ft_strcmp(args_cmd[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(args_cmd[0], "echo") == 0)
		ft_echo(data, args_cmd);
	else if (ft_strcmp(args_cmd[0], "unset") == 0)
		ft_unset(data, args_cmd);
	else if (ft_strcmp(args_cmd[0], "export") == 0)
		ft_export(data, args_cmd);
	if (cmd_process < data->nbr_of_command - 1)
        close(data->current_pipe[1]);
	dup2(data->stdout_backup, STDOUT_FILENO);
	dup2(data->stdin_backup, STDIN_FILENO);
	data->is_builtin_cmd[cmd_process] = true;
	return (0);
}
