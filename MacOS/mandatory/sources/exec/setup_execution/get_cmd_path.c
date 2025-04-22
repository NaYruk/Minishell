/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:36:58 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/17 21:03:16 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	add_slash :
	Appends a slash ('/') to each path in the all_paths array.
	Iterates through the all_paths array, adding a slash to each path.
	Frees the original path and replaces
	it with the new path containing the slash.
	If memory allocation fails,
	frees all previously allocated paths and calls malloc_error.
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
	Extracts and processes the PATH environment
	variable to obtain all command paths.
	Searches the environment variables for the PATH variable.
	Extracts the value of the PATH variable and splits
	it into individual paths.
	Appends a slash ('/') to each path using the add_slash function.
	Returns an array of all command paths or NULL
	if the PATH variable is not found.
	Handles memory allocation errors
	by calling malloc_error if allocation fails.
*/

static char	**get_all_cmd_paths(t_data *data)
{
	int		i;
	char	*path_line;
	char	**all_paths;

	i = 0;
	all_paths = NULL;
	path_line = NULL;
	while ((data->env[i] != NULL) && !ft_strnstr(data->env[i], "PATH=", 5))
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
** find_cmd_path:
** - This function searches for the full path of a command
**		in the provided command paths.
** - Iterates through the `all_cmd_paths` array, appending
**		the command name to each path.
** - Checks if the resulting path exists and is executable using `access`.
** - Sets `data->exec->cmd_path` to the first valid path found.
** - Frees all allocated memory for paths and the command
**		path array after processing.
** - Handles memory allocation errors by calling `malloc_error` if necessary.
*/

int	find_cmd_path(t_data *data, char **all_cmd_paths,
		t_token **current, int *i)
{
	char	*test_cmd_path;

	test_cmd_path = NULL;
	if (all_cmd_paths && (*current)->line[0] != '\0')
	{
		while (all_cmd_paths[++(*i)] != NULL)
		{
			test_cmd_path = ft_strjoin(all_cmd_paths[*i], (*current)->line);
			if (!test_cmd_path)
				malloc_error(data);
			if (access(test_cmd_path, F_OK) == 0)
			{
				data->exec->cmd_path = test_cmd_path;
				break ;
			}
			free(test_cmd_path);
		}
		*i = -1;
		while (all_cmd_paths[++(*i)] != NULL)
			free(all_cmd_paths[(*i)]);
		free(all_cmd_paths);
		return (1);
	}
	return (0);
}

/*
	get_cmd_path :
	Determines the full path of a command specified in the current token.
	First, checks if the command is an absolute path
	and executable using check_absolute_cmd.
	If not, retrieves all command paths from
	the PATH environment variable using get_all_cmd_paths.
	Iterates through each path, appending the command name
	and checking if the resulting path is executable.
	Sets data->exec->cmd_path to the first executable path found.
	Frees allocated memory for paths and the command path array.
*/

int	get_cmd_path(t_data *data, t_token **current)
{
	char	**all_cmd_paths;
	int		i;

	i = -1;
	all_cmd_paths = get_all_cmd_paths(data);
	if (find_cmd_path(data, all_cmd_paths, current, &i) == 1)
		all_cmd_paths = NULL;
	if (check_validity_cmd(data, current) == -2)
	{
		if (all_cmd_paths != NULL)
		{
			i = -1;
			while (all_cmd_paths[++i] != NULL)
				free(all_cmd_paths[i]);
			free(all_cmd_paths);
			all_cmd_paths = NULL;
		}
		return (-1);
	}
	return (0);
}
