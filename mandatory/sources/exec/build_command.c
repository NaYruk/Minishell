/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:03:55 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/07 18:21:12 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_command_args(t_data *data, t_token *current)
{
	t_token	*token;
	int	count;
	int i;
	
	token = current;
	count = 0;
	i = 0;
	while (token != NULL && (token->token == ARG || token->token == CMD))
	{
		count++;
		token = token->next;
	}
	data->exec->arg = malloc(sizeof(char **) * (count + 1));
	if (!data->exec->arg)
		malloc_error(data);
	token = current;
	while (token != NULL && (token->token == CMD || token->token == ARG))
	{
		data->exec->arg[i] = ft_strdup(token->line);
		if (!data->exec->arg[i])
			malloc_error(data);
		token = token->next;
		i++;
	}
	data->exec->arg[i] = NULL;
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
	tmp = NULL;
	tmp = ft_strdup(current->line);
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
