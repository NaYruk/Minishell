/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:27:10 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/23 02:54:52 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../..//includes/minishell.h"

/*
** redirect_heredoc:
** - This function handles input redirection from a heredoc.
** - Checks if the current redirection is of type HEREDOC
**		and is the last one in the list.
** - Redirects `STDIN` to the heredoc file descriptor using `dup2`.
** - Closes the heredoc file descriptor after redirection is set up.
*/
/* REDIRECT_INFILE = In the case of we have a infile
					  redirect STDIN in the infile 
					 In the case of we have a heredoc
					  redirect STDIN is last pipe heredoc */

int	redirect_infile_heredoc(t_data *data,
		t_exec_redir *current)
{
	int	fd_file;

	fd_file = 0;
	if (current != NULL && current->type == INFILE)
	{
		fd_file = open(current->arg, O_RDONLY);
		if (fd_file == -1)
		{
			perror(current->arg);
			return (data->exit_status = 1, -1);
		}
		if (dup2(fd_file, STDIN_FILENO) == -1)
			error(data, "dup2");
		close (fd_file);
	}
	if (current != NULL && current->type == HEREDOC)
	{
		if (last_heredoc(current) == true)
		{
			if (dup2(data->heredoc_fd[data->hd_index], STDIN_FILENO) == -1)
				error(data, "dup2");
		}
	}
	return (0);
}

/* REDIRECT_OUTFILE = In the case of we have a outfile
					   redirect STDOUT in the outfile */

int	redirect_outfile(t_data *data, t_exec_redir *current)
{
	int	fd_file;

	fd_file = 0;
	if (current != NULL && current->type == OUTFILE)
	{
		fd_file = open(current->arg,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_file == -1)
		{
			perror(current->arg);
			data->exit_status = 1;
			return (-1);
		}
		if (dup2(fd_file, STDOUT_FILENO) == -1)
			error(data, "dup2");
		close(fd_file);
	}
	return (0);
}

/* REDIRECT_APPEND = In the case of we have a append
					  redirect STDOUT in the append */

int	redirect_append(t_data *data, t_exec_redir *current)
{
	int	fd_file;

	fd_file = 0;
	if (current != NULL && current->type == APPEND)
	{
		fd_file = open(current->arg,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_file == -1)
		{
			perror(current->arg);
			data->exit_status = 1;
			return (-1);
		}
		if (dup2(fd_file, STDOUT_FILENO) == -1)
			error(data, "dup2");
		close(fd_file);
	}
	return (0);
}

/*
	REDIRECT_PIPES :
	if the command is not the first, redirect the STDIN in the last pipe
	if the command is not the lastm redirect the STDOUT in the actual pipe.
*/

void	redirect_pipes(t_data *data, int cmd_process)
{
	if ((data->part_of_line - 1) > 0 && data->old_read_pipe != -1)
	{
		if (dup2(data->old_read_pipe, STDIN_FILENO) == -1)
			error(data, "dup2");
		if ((data->part_of_line - 2) > 0)
			close(data->old_read_pipe);
	}
	if (cmd_process < (data->part_of_line - 1))
	{
		if (dup2(data->current_pipe[1], STDOUT_FILENO) == -1)
			error(data, "dup2");
		close(data->current_pipe[1]);
	}
	if ((data->part_of_line - 1) > 0 || cmd_process < (data->part_of_line - 1))
		close(data->current_pipe[0]);
	return ;
}

/*
** setup_redirection:
** - This function sets up all necessary redirection before executing a command
** - Redirects `STDIN` and `STDOUT` based on
**		the command's position in the pipeline.
** - Handles input redirection from files or heredocs
**		and output redirection to files or append mode.
** - Iterates through the redirection list and applie each redirection in order
** - Returns 0 on success or -1 if an error occurs during redirection setup.
*/

int	setup_redirection(t_data *data, int cmd_process)
{
	t_exec_redir	*current;

	current = data->exec->t_exec_redir;
	redirect_pipes(data, cmd_process);
	while (current != NULL)
	{
		if (redirect_infile_heredoc(data, current) == -1)
			return (-1);
		if (redirect_outfile(data, current) == -1)
			return (-1);
		if (redirect_append(data, current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}
