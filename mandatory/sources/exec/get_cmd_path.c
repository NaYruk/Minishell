/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:36:58 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/31 15:15:42 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	add_slash :
	Appends a slash ('/') to each path in the all_paths array.
	Iterates through the all_paths array, adding a slash to each path.
	Frees the original path and replaces it with the new path containing the slash.
	If memory allocation fails, frees all previously allocated paths and calls malloc_error.
*/

static void	add_slash(t_data *data, char **all_paths, char *path_line, int *i)
{
	*i = -1;
	while (all_paths[++(*i)] != NULL)
	{
		path_line = ft_strjoin(all_paths[*i], "/");
		free(all_paths[*i]);
		all_paths[*i] = path_line;
		if (!all_paths[*i])
		{
			while (--(*i) >= 0)
				free(all_paths[*i]);
			free(all_paths);
			malloc_error(data);
		}
	}
}

/*
	get_all_cmd_paths :
	Extracts and processes the PATH environment variable to obtain all command paths.
	Searches the environment variables for the PATH variable.
	Extracts the value of the PATH variable and splits it into individual paths.
	Appends a slash ('/') to each path using the add_slash function.
	Returns an array of all command paths or NULL if the PATH variable is not found.
	Handles memory allocation errors by calling malloc_error if allocation fails.
*/


static char	**get_all_cmd_paths(t_data *data)
{
	int		i;
	char	*path_line;
	char	**all_paths;

	i = 0;
	all_paths = NULL;
	path_line = NULL;
	while (!ft_strnstr(data->env[i], "PATH=", 5) && (data->env[i] != NULL))
		i++;
	if (!data->env[i])
		return (NULL);
	path_line = ft_substr(data->env[i], 5, ft_strlen(data->env[i]));
	if (!path_line)
		malloc_error(data);
	all_paths = ft_split(path_line, ':');
	free(path_line);
	if (!all_paths)
		malloc_error(data);
	path_line = NULL;
	add_slash(data, all_paths, path_line, &i);
	return (all_paths);
}

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

int	check_absolute_cmd(t_data *data, t_token **current, char *test_cmd_path)
{
	if (check_dir(data, *current, 0) == -1)
		return (-2);
	else if (access((*current)->line, F_OK) == 0 && !check_dir(data, *current, 1))
	{
		if (access((*current)->line, X_OK) == -1 && (ft_strncmp((*current)->line, "./", 2) == 0 || ft_strncmp((*current)->line, "/", 1) == 0))
		{
			ft_putstr_fd((*current)->line, 2);
			ft_putstr_fd(": Permission denied\n", 2);
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
	if (!data->exec->cmd_path && !exec_build((*current)->line) && (ft_strncmp((*current)->line, "./", 2) == 0 || ft_strncmp((*current)->line, "/", 1) == 0))
	{
		ft_putstr_fd((*current)->line, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_status = 127;
		return (-2);
	}
	else if (!data->exec->cmd_path && !exec_build((*current)->line))
	{
		ft_putstr_fd((*current)->line, 2);
		ft_putstr_fd(": command not found\n", 2);
		data->exit_status = 127;
		return (-2);
	}
	return (0);
}

/*
	get_cmd_path :
	Determines the full path of a command specified in the current token.
	First, checks if the command is an absolute path and executable using check_absolute_cmd.
	If not, retrieves all command paths from the PATH environment variable using get_all_cmd_paths.
	Iterates through each path, appending the command name and checking if the resulting path is executable.
	Sets data->exec->cmd_path to the first executable path found.
	Frees allocated memory for paths and the command path array.
*/

int	get_cmd_path(t_data *data, t_token **current)
{
	char	**all_cmd_paths;
	char	*test_cmd_path;
	int		i;

	i = -1;
	test_cmd_path = NULL;
	all_cmd_paths = get_all_cmd_paths(data);
	if (!all_cmd_paths)
		return (-1);
	while (all_cmd_paths[++i] != NULL)
	{
		test_cmd_path = ft_strjoin(all_cmd_paths[i], (*current)->line);
		if (!test_cmd_path)
            malloc_error(data);
		if (access(test_cmd_path, F_OK) == 0)
		{
			data->exec->cmd_path = test_cmd_path;
			break ;
		}
		free(test_cmd_path);
	}
	i = -1;
	while (all_cmd_paths[++i] != NULL)
		free(all_cmd_paths[i]);
	free(all_cmd_paths);
	if (check_absolute_cmd(data, current, test_cmd_path) == -2)
		return (-1);
	return (0);
}
