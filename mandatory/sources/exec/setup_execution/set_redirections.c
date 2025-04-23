/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:23:42 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/23 02:55:52 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** set_append:
** - This function sets up an append redirection for the current command.
** - Checks if the current token is of type APPEND
**		and the next token is an argument.
** - Adds a new redirection node to the execution structure's redirection list.
** - Opens the specified file in append mode, creating it if it does not exist.
** - Returns 0 on success or -1 if the file cannot be opened or an error occurs
*/

int	set_append(t_data *data, t_token *current)
{
	int	fd_file;

	fd_file = 0;
	if (current->token == APPEND && (current->next->token) == ARG)
	{
		add_new_redir_node(data, &data->exec->t_exec_redir,
			current->next->line, APPEND);
		if (current->next->line != NULL)
		{
			fd_file = open(current->next->line,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_file == -1)
			{
				perror(current->next->line);
				data->error_built = 1;
				data->exit_status = 1;
				return (-1);
			}
			close(fd_file);
		}
	}
	return (0);
}

/*
** set_outfile:
** - This function sets up an output redirection for the current command.
** - Checks if the current token is of type OUTFILE
**		and the next token is an argument.
** - Adds a new redirection node to the execution structure's redirection list.
** - Opens the specified file in write mode, creating it if it does not exist.
** - Returns 0 on success or -1 if the file cannot be opened or an error occurs
*/

int	set_outfile(t_data *data, t_token *current)
{
	int	fd_file;

	fd_file = 0;
	if (current->token == OUTFILE && (current->next->token) == ARG)
	{
		add_new_redir_node(data, &data->exec->t_exec_redir,
			current->next->line, OUTFILE);
		fd_file = open(current->next->line,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_file == -1)
		{
			perror(current->next->line);
			data->error_built = 1;
			data->exit_status = 1;
			return (-1);
		}
		close(fd_file);
	}
	return (0);
}

/*
** set_infile:
** - This function sets up an input redirection for the current command.
** - Checks if the current token is of type INFILE
**		and the next token is an argument.
** - Adds a new redirection node to the execution structure's redirection list.
** - Verifies that the specified file exists and is readable using `access`.
** - Returns 0 on success or -1 if the file is inaccessible or an error occurs.
*/

int	set_infile(t_data *data, t_token *current)
{
	if (current->token == INFILE && (current->next->token) == ARG)
	{
		add_new_redir_node(data, &data->exec->t_exec_redir,
			current->next->line, INFILE);
		if (access(current->next->line, F_OK | R_OK) == -1)
		{
			perror(current->next->line);
			data->error_built = 1;
			data->exit_status = 1;
			return (-1);
		}
	}
	return (0);
}

/*
** set_heredoc:
** - This function sets up a heredoc redirection for the current command.
** - Checks if the current token is of type HEREDOC
**		and the next token is an argument.
** - Adds a new redirection node to the execution structure's redirection list.
** - Stores the heredoc delimiter (argument) in the redirection
**		node for later processing.
** - Returns 0 on success.
*/

int	set_heredoc(t_data *data, t_token *current)
{
	if (current->token == HEREDOC && (current->next->token) == ARG)
	{
		add_new_redir_node(data, &data->exec->t_exec_redir,
			current->next->line, HEREDOC);
		data->heredoc_in_pipe = 1;
	}
	return (0);
}
