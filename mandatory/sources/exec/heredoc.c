/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:01:44 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/25 23:20:22 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

/*
	read_heredoc_to_pipe - Reads user input until the delimiter is reached
	and writes it to the given pipe.
*/

void	read_heredoc_to_pipe(int write_pipe, char *delimiter)
{
	char	*line;
	
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putstr_fd(line, write_pipe);
		ft_putstr_fd("\n", write_pipe);
	}
	if (line)
		free(line);
	return ;
}

/*
	exec_heredoc - Handles heredoc execution by creating pipes and storing
	the last heredoc's read end for input redirection.
*/

int	exec_heredoc(t_data *data)
{
	int	i;
	int	pipefd[2];
	
	i = -1;
	data->exec->last_heredoc_fd = -1;
	while (data->exec->heredoc[++i] != NULL)
	{
		if (pipe(pipefd) == -1)
		{
			perror("Pipe");
			return (-1);
		}
		read_heredoc_to_pipe(pipefd[1], data->exec->heredoc[i]);
		close(pipefd[1]);
		if (data->exec->last_heredoc_fd != -1)
			close(data->exec->last_heredoc_fd);
		data->exec->last_heredoc_fd = pipefd[0];
	}
	return (0);
}