/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:09:46 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/11 18:19:33 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	setup_redirection(t_data *data, int cmd_process, int (*pipes)[2])
{
	int	fd_file;
	
	(void)pipes;
	fd_file = 0;
	if (cmd_process == 0)
	{
		if (data->exec->infile != NULL)
		{
			fd_file = open(data->exec->infile, O_RDONLY);
			if (fd_file == -1)
			{
				perror(data->exec->infile);
				exit(EXIT_FAILURE);
			}
			dup2(fd_file, STDIN_FILENO);
			close (fd_file);
		}
		if (data->exec->outfile != NULL)
		{
			fd_file = open(data->exec->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_file == -1)
			{
				perror(data->exec->outfile);
				exit(EXIT_FAILURE);
			}
			dup2(fd_file, STDOUT_FILENO);
			close(fd_file);
		}
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
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}