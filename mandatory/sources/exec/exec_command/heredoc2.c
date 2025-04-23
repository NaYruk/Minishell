/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:01:44 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/23 02:24:17 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** last_heredoc:
** - This function checks if the current heredoc redirection
**        is the last one in the list.
** - Iterates through the redirection list starting from the current node.
** - Returns `true` if no other heredoc redirections
**        are found after the current node.
** - Returns `false` if another heredoc redirection is detected.
*/

bool	last_heredoc(t_exec_redir *current)
{
	t_exec_redir	*current_start;

	current_start = current;
	if (current->next)
		current = current->next;
	else
		return (true);
	while (current != NULL)
	{
		if (current->type == HEREDOC)
		{
			current = current_start;
			return (false);
		}
		current = current->next;
	}
	current = current_start;
	return (true);
}

/*
** catch_signal:
** - This function handles signals and EOF during heredoc input processing.
** - If a signal (e.g., SIGINT) is detected, it restores the original
**        `STDIN` and closes the file descriptor.
** - Displays a warning if the heredoc is terminated by EOF instead
**        of the expected delimiter.
** - Updates the shell's exit status if interrupted by a signal.
** - Returns `true` if a signal or EOF is caught, otherwise returns `false`.
*/

bool	catch_signal(t_data *data, char *line, char *delimiter)
{
	if (!line || g_signal == SIGINT)
	{
		if (data->stdin_backup != -1)
		{
			if (dup2(data->stdin_backup, STDIN_FILENO))
				error(data, "dup2");
		}
		if (!line && g_signal != SIGINT)
		{
			ft_putstr_fd("warning: here-document delimited by EOF.", 2);
			ft_putstr_fd("Wanted: '", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("'.\n", 2);
			data->exit_status = 0;
		}
		if (g_signal == SIGINT)
			update_exit_status(data);
		return (true);
	}
	return (false);
}

/*
** nbr_of_heredoc:
** - This function counts the number of heredocs in the token list.
** - Iterates through the token list, identifying tokens of type HEREDOC.
** - Ensures that only one heredoc per pipeline segment is counted.
** - Returns the total number of heredocs detected in the token list.
*/

int	nbr_of_heredoc(t_data *data)
{
	bool	heredoc_detected_in_pipe;
	int		nbr;
	t_token	*current;

	nbr = 0;
	current = data->lst_token;
	heredoc_detected_in_pipe = false;
	while (current != NULL)
	{
		if (current->token == PIPE)
			heredoc_detected_in_pipe = false;
		else if (current->token == HEREDOC && heredoc_detected_in_pipe == false)
		{
			heredoc_detected_in_pipe = true;
			nbr++;
		}
		current = current->next;
	}
	return (nbr);
}

/*
** malloc_heredoc_fd:
** - This function allocates memory for the file descriptors used by heredocs.
** - Creates an array of pipes, one for each heredoc, to store their input.
** - Adds the allocated memory to the garbage collector for proper cleanup.
** - Handles errors during memory allocation or
**        pipe creation by calling `malloc_error` or `error`.
*/

void	malloc_heredoc_fd(t_data *data, int nbr)
{
	if (nbr == 0)
		return ;
	else
	{
		data->heredoc_fd = malloc(sizeof(int) * data->nbr_heredoc);
		if (!data->heredoc_fd)
			malloc_error(data);
		add_g_c_node(data, &data->g_c, (void **)data->heredoc_fd, false);
		ft_memset(data->heredoc_fd, -1, sizeof(int) * data->nbr_heredoc);
	}
	return ;
}

/*
** close_fd:
** - This function closes all file descriptors associated
**        with heredocs up to a given index.
** - Iterates through the heredoc file descriptor array
**        and closes both read and write ends.
** - Ensures proper cleanup of resources to prevent file descriptor leaks.
*/

void	close_heredoc_fd(t_data *data)
{
	int	index;

	index = 0;
	if (data->nbr_heredoc > 0)
	{
		while (index <= data->nbr_heredoc - 1)
		{
			if (data->heredoc_fd[index] != -1)
				close (data->heredoc_fd[index]);
			index++;
		}
	}
	return ;
}
