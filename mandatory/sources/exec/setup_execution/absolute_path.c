/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:31:22 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/08 03:13:50 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	CHECK_DIR = Function to verify if a command path is a directory.

	This function checks if the command path specified in data->exec->cmd_path is a
	directory. If the path is a directory, it prints an error message and sets the
	exit status to 126. If the path is not a directory, the function returns 0.
*/

int	check_dir(t_data *data, t_token *current, int mode)
{
	struct stat	stat_file;

	if (stat(current->line, &stat_file) == -1)
        return (0);
	if (mode == 1)
		if (S_ISDIR(stat_file.st_mode))
			return (1);
	if (S_ISDIR(stat_file.st_mode) && strchr(current->line, '/'))
	{
		ft_putstr_fd(current->line, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		data->exit_status = 126;
		return (-1);
	}
	return (0);
}

/*
	check_absolute_cmd :
	Checks if the command in the current token is an executable file.
	Uses the access function to determine if the file exists and is executable.
	If the file is executable, duplicates the command path and assigns it to data->exec->cmd_path.
	Returns -1 if the command is executable, otherwise returns 0.
*/

int	check_absolute_cmd(t_data *data, t_token **current, char *test_cmd_path, char **all_cmd_path)
{
	if (check_dir(data, *current, 0) == -1)
		return (-2);
	else if (access((*current)->line, F_OK) == 0 && !check_dir(data, *current, 1))
	{
		if (access((*current)->line, X_OK) == -1 && (ft_strncmp((*current)->line, "./", 2) == 0 || ft_strncmp((*current)->line, "/", 1) == 0))
		{
			ft_putstr_fd((*current)->line, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			data->error_built = 1;
			data->exit_status = 126;
			return (-2);
		}
		else if (access((*current)->line, X_OK) == 0)
		{
			test_cmd_path = ft_strdup((*current)->line);
			data->exec->cmd_path = test_cmd_path;
			return (-1);
		}
	}
	if (!data->exec->cmd_path && !exec_build((*current)->line) && ((ft_strncmp((*current)->line, "./", 2) == 0 || ft_strncmp((*current)->line, "/", 1) == 0) || !all_cmd_path))
	{
		ft_putstr_fd((*current)->line, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_status = 127;
		data->error_built = 1;
		return (-2);
	}
	else if (!data->exec->cmd_path && (!exec_build((*current)->line)))
	{
		ft_putstr_fd((*current)->line, 2);
		ft_putstr_fd(": command not found\n", 2);
		data->exit_status = 127;
		data->error_built = 1;
		return (-2);
	}
	return (0);
}