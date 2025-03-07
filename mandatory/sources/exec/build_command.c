/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:03:55 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/07 15:31:11 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_command_args(t_data *data, t_token *current)
{
	int	count;
	int i;
	
	count = 0;
	i = -1;
	current = current->next;
	while (current != NULL && current->token == ARG)
	{
		count++;
		current = current->next;
	}
	data->exec->arg = malloc(sizeof(char **) * (count + 1));
	if (!data->exec->arg)
		malloc_error(data);
	while (current != NULL && current->token != CMD)
		current = current->prev;
	while (current != NULL && (current->token == ARG || current->token == CMD))
	{
		data->exec->arg[i] = ft_strdup(current->line);
		if (!data->exec->arg[i])
			malloc_error(data);
		current = current->next;
	}
	return ;
}

char	*find_command_path(t_data *data, t_token *current)
{
	int		i;
	char	*tmp;

	i = -1;
	while (data->exec->path_cmd_env[++i] != NULL)
	{
		tmp = ft_strjoin(data->exec->path_cmd_env[i], current->line);
		if (!tmp)
			malloc_error(data);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		free(tmp);
	}
	tmp = ft_strjoin(current->line, "");
	if (!tmp)
		malloc_error(data);
	if (access(tmp, F_OK | X_OK) == 0)
		return (tmp);
	free(tmp);
	return (NULL);
}

/* 
	Function for find the PATH environnement variable
	and stock each path in a char *
	for find after that the command path.
*/

void	find_path_env(t_data *data)
{
	char	*tmp;
	char	*path_line;
	int		i;

	i = 0;
	path_line = NULL;
	tmp = NULL;
	path_line = data->env[i];
	while (!ft_strnstr(path_line, "PATH=", 5) && (data->env[i] != NULL))
		path_line = data->env[++i];
	path_line = ft_substr(path_line, 5, ft_strlen(path_line));
	data->exec->path_cmd_env = ft_split(path_line, ':');
	if (!data->exec->path_cmd_env)
		malloc_error(data);
	i = -1;
	while (data->exec->path_cmd_env[++i] != NULL)
	{
		tmp = ft_strjoin(data->exec->path_cmd_env[i], "/");
		free(data->exec->path_cmd_env[i]);
		data->exec->path_cmd_env[i] = tmp;
	}
	free(path_line);
	return ;
}
