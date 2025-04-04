/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:01:44 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/04 19:53:27 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	read_heredoc_to_pipe(t_data *data, int write_pipe, t_token *current)
{
	char	*line;
	char	*delimiter;
	t_token	*heredoc_token;
	
	line = NULL;
	delimiter = current->line;
	heredoc_token = current;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (heredoc_token)
		{
			if (heredoc_token->quote_char == '\0')
				replace_dollars(data, &line);
		}
		ft_putstr_fd(line, write_pipe);
		ft_putstr_fd("\n", write_pipe);
		free(line);
	}
}

/*
	exec_heredoc - Handles heredoc execution by creating pipes and storing
	the last heredoc's read end for input redirection.
*/

int	exec_heredoc(t_data *data, t_token *current)
{
	int	pipefd[2];
	
	if (pipe(pipefd) == -1)
	{
		perror("Pipe");
		return (-1);
	}
	read_heredoc_to_pipe(data, pipefd[1], current);
	close(pipefd[1]);
	if (data->exec->last_heredoc_fd != -1)
		close(data->exec->last_heredoc_fd);
	data->exec->last_heredoc_fd = pipefd[0];
	return (0);
}
