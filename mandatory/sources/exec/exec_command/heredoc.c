/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:01:44 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/23 01:58:43 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** read_heredoc_to_pipe:
** - This function reads input for a heredoc
**		and writes it to the specified pipe.
** - Prompts the user for input until the delimiter is encountered
**		or a signal interrupts the process.
** - Trims the newline character from each input line and compares
**		it to the delimiter.
** - Writes valid input lines to the pipe and frees
**		allocated memory for each line.
** - Handles signals during heredoc processing
**		and exits gracefully if interrupted.
*/

void	read_heredoc_to_pipe(t_data *data, int write_pipe, t_token *current)
{
	char	*line;
	char	*delimiter;

	delimiter = current->line;
	line = NULL;
	setup_signals_heredoc();
	g_signal = 0;
	while (1)
	{
		line = readline("> ");
		if (catch_signal(data, line, delimiter) == true)
			return ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return ;
		}
		replace_dollars(data, &line);
		ft_putstr_fd(line, write_pipe);
		ft_putstr_fd("\n", write_pipe);
		free(line);
	}
}

/*
** read_heredoc:
** - This function handles the processing of a single heredoc token.
** - Creates a pipe to store the heredoc input and writes the input to the pipe
** - Reads lines from the user until the delimiter is encountered
**		or a signal interrupts the process.
** - Closes the write end of the pipe after writing the heredoc input.
** - Returns 0 on success or 1 if interrupted by a signal (e.g., SIGINT).
*/

int	read_heredoc(t_data *data, t_token *current, int tmp[2],
		bool *heredoc_detected_in_pipe)
{
	if (current->token == HEREDOC && current->next
		&& current->next->token == ARG)
	{
		if (*heredoc_detected_in_pipe)
			close(tmp[0]);
		if (pipe(tmp) == -1)
			error(data, "PIPE");
		read_heredoc_to_pipe(data, tmp[1], current->next);
		close(tmp[1]);
		if (g_signal == SIGINT)
		{
			close(tmp[0]);
			return (1);
		}
		*heredoc_detected_in_pipe = true;
		setup_signals_interactive();
	}
	return (0);
}

/*
** exec_heredoc2:
** - This function processes all heredocs in the token list and stores
**		their input in pipes.
** - Reads heredoc input for each token of type HEREDOC and writes
**		it to a temporary pipe.
** - Handles heredocs within pipelines, ensuring proper pipe management.
** - Closes unused file descriptors and stores the read end
**		of the pipe for later use.
** - Returns 0 on success or 1 if interrupted by a signal (e.g., SIGINT).
*/

int	exec_heredoc2(t_data *data, t_token *current, int tmp[2])
{
	int		hd_index;
	bool	heredoc_detected_in_pipe;

	hd_index = 0;
	heredoc_detected_in_pipe = false;
	while (current != NULL)
	{
		if (read_heredoc(data, current, tmp, &heredoc_detected_in_pipe) == 1)
			return (close_heredoc_fd(data), 1);
		if (current->token == PIPE || !current->next)
		{
			if (heredoc_detected_in_pipe)
			{
				data->heredoc_fd[hd_index] = tmp[0];
				hd_index++;
			}
			heredoc_detected_in_pipe = false;
		}
		current = current->next;
	}
	return (0);
}

/*
** exec_heredoc:
** - This function manages the execution of all heredoc in the command pipeline
** - Counts the number of heredocs and allocates file descriptors for them.
** - Iterates through the token list, reading heredoc
**		input and storing it in pipes.
** - Handles signals like `SIGINT` to interrupt heredoc processing.
** - Returns 0 on success or -1 if an error occurs
**		(e.g., interrupted by a signal).
*/

int	exec_heredoc(t_data *data)
{
	t_token	*current;
	int		tmp[2];

	data->nbr_heredoc = nbr_of_heredoc(data);
	if (data->nbr_heredoc == 0)
		return (0);
	current = data->lst_token;
	malloc_heredoc_fd(data, data->nbr_heredoc);
	if (exec_heredoc2(data, current, tmp) == 1)
	{
		g_signal = 0;
		setup_signals_interactive();
		return (-1);
	}
	return (0);
}
