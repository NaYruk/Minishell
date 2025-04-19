/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:31:22 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/19 01:32:22 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	CHECK_DIR = Function to verify if a command path is a directory.

	This function checks if the command path
	specified in data->exec->cmd_path is a
	directory. If the path is a directory, it prints an
	error message and sets the
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
** check_permissions:
** - This function checks if the command has
**		the necessary permissions for execution.
** - Verifies if the command exists using `access` with `F_OK`.
** - Checks if the command is executable using `access` with `X_OK`.
** - Handles cases where the command is a directory
**		or lacks execution permissions.
** - Updates the shell's exit status and error flags for permission errors.
** - Returns -2 for permission errors, -1 if the command is valid,
**		or 0 otherwise.
*/

int	check_permissions(t_data *data, t_token **current, char **test_cmd_path)
{
	if (access((*current)->line, F_OK) == 0 && !check_dir(data, *current, 1))
	{
		if (access((*current)->line, X_OK) == -1
			&& (ft_strncmp((*current)->line, "./", 2) == 0
				|| ft_strncmp((*current)->line, "/", 1) == 0))
		{
			ft_putstr_fd((*current)->line, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			data->error_built = 1;
			data->exit_status = 126;
			return (-2);
		}
		else if (access((*current)->line, X_OK) == 0)
		{
			*test_cmd_path = ft_strdup((*current)->line);
			if (!(*test_cmd_path))
				malloc_error(data);
			data->exec->cmd_path = *test_cmd_path;
			return (-1);
		}
	}
	return (0);
}

/* Function for check if the PATH envionnement variable is unset or not */

bool	path_unset(t_data *data)
{
	int	i;

	i = -1;
	if (data->env)
	{
		while (data->env[++i] != NULL)
		{
			if (ft_strnstr(data->env[i], "PATH=", 5))
				return (false);
		}
	}
	return (true);
}

/*
** check_existing:
** - This function checks if the command exists and is valid for execution.
** - Handles cases where the command is a relative or absolute 
**		path but does not exist.
** - Displays appropriate error messages for missing files or invalid commands.
** - Updates the shell's exit status and error flags based on the type of error
** - Returns 0 if the command exists, or -2 if it does not exist or is invalid.
*/

int	check_existing(t_data *data, t_token **current)
{
	if (!data->exec->cmd_path && !exec_build((*current)->line)
		&& ((ft_strncmp((*current)->line, "./", 2) == 0
				|| ft_strncmp((*current)->line, "/", 1) == 0
				|| path_unset(data))))
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

/*
** check_absolute_cmd:
** - This function verifies if a command is an absolute or relative path.
** - Checks if the command is a directory and handles errors accordingly.
** - Validates file permissions to ensure the command is executable.
** - Handles cases where the command does not exist or is not found in the PATH
** - Returns 0 on success, -1 for permission errors, or -2 for other errors.
*/

int	check_validity_cmd(t_data *data, t_token **current)
{
	int		status;
	char	*test_cmd_path;

	if (check_dir(data, *current, 0) == -1)
		return (-2);
	status = check_permissions(data, current, &test_cmd_path);
	if (status != 0)
		return (status);
	status = check_existing(data, current);
	if (status != 0)
		return (status);
	return (0);
}
