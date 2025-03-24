/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:36:58 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/23 19:41:25 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

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

int	check_absolute_cmd(t_data *data, t_token **current, char *test_cmd_path)
{
	if (access((*current)->line, F_OK | X_OK) == 0)
	{
		test_cmd_path = ft_strdup((*current)->line);
		data->exec->cmd_path = test_cmd_path;
		return (-1);
	}
	return (0);
}

void	get_cmd_path(t_data *data, t_token **current)
{
	char	**all_cmd_paths;
	char	*test_cmd_path;
	int		i;

	i = -1;
	test_cmd_path = NULL;
	if (check_absolute_cmd(data, current, test_cmd_path) == -1)
		return ;
	all_cmd_paths = get_all_cmd_paths(data);
	if (!all_cmd_paths)
		return ;
	while (all_cmd_paths[++i] != NULL)
	{
		test_cmd_path = ft_strjoin(all_cmd_paths[i], (*current)->line);
		if (access(test_cmd_path, F_OK | X_OK) == 0)
		{
			data->exec->cmd_path = test_cmd_path;
			break ;
		}
		free(test_cmd_path);
	}
	if (data->exec->cmd_path == NULL)
		data->exec->cmd_path = (*current)->line;
	i = -1;
	while (all_cmd_paths[++i] != NULL)
		free(all_cmd_paths[i]);
	free(all_cmd_paths);
}
