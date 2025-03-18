/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:09:46 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/19 00:09:06 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	setup_redirection(t_data *data, int cmd_process, int (*pipes)[2])
{
	int	fd_file;
	int	i;
	
	i = 0;
	fd_file = 0;
	if (cmd_process > 0)
		dup2(pipes[cmd_process - 1][0], STDIN_FILENO);
	if (cmd_process < data->nbr_of_command - 1)
		dup2(pipes[cmd_process][1], STDOUT_FILENO);
	while (data->exec->infile[i] != NULL)
	{
		fd_file = open(data->exec->infile[i], O_RDONLY);
		if (fd_file == -1)
		{
			perror(data->exec->infile[i]);
			exit(EXIT_FAILURE);
		}
		dup2(fd_file, STDIN_FILENO);
		close (fd_file);
		i++;
	}
	i = 0;
	while (data->exec->outfile[i] != NULL)
	{
		fd_file = open(data->exec->outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_file == -1)
		{
			perror(data->exec->outfile[i]);
			exit(EXIT_FAILURE);
		}
		dup2(fd_file, STDOUT_FILENO);
		close(fd_file);
		i++;
	}
	i = 0;
	while (data->exec->append[i] != NULL)
	{
		fd_file = open(data->exec->append[i], O_WRONLY| O_CREAT | O_APPEND, 0644);
		if (fd_file == -1)
		{
			perror(data->exec->append[i]);
			exit(EXIT_FAILURE);
		}
		dup2(fd_file, STDOUT_FILENO);
		close(fd_file);
		i++;
	}
	return (0);
}

int	child_process(t_data *data, int i, int (*pipes)[2])
{
	if (setup_redirection(data, i, pipes) == -1)
	{
		close_pipes(data, pipes);
		exit(EXIT_FAILURE);
	}
	close_pipes(data, pipes);
	if (execve(data->exec->cmd_path, data->exec->arg_cmd, data->env) == -1)
	{
		ft_putstr_fd(data->exec->arg_cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	exit(0);
}