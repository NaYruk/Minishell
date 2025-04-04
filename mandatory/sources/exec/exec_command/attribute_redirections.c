/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:27:10 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/04 12:41:19 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

/* REDIRECT_INFILE = In the case of we have a infile
					  redirect STDIN in the infile */
			  
int	redirect_infile(t_data *data, t_exec_redir *current)
{
	int	fd_file;

	fd_file = 0;
	if (current != NULL && current->type == INFILE)
	{
		fd_file = open(current->arg, O_RDONLY);
		if (fd_file == -1)
		{
			perror(current->arg);
			data->exit_status = 1;
			return (-1);
		}
		dup2(fd_file, STDIN_FILENO);
		close (fd_file);
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
		dup2(fd_file, STDOUT_FILENO);
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
		dup2(fd_file, STDOUT_FILENO);
		close(fd_file);
	}
	return (0);
}

/* REDIRECT_HEREDOC = In the case of we have a heredoc
					  redirect STDIN is last pipe heredoc */
					  
void	redirect_heredoc(t_data *data, t_exec_redir *current)
{
	if (current != NULL && current->type == HEREDOC)
	{
		exec_heredoc(data, current);
		dup2(data->exec->last_heredoc_fd, STDIN_FILENO);
		close(data->exec->last_heredoc_fd);
	}
}

/* 
	SETUP_REDIRECTION = Function for setup each redirection
					   before the execution of a command 
	
	if the command is not the first, redirect the STDIN in the last pipe
	if the command is not the lastm redirect the STDOUT in the actual pipe.
	REDIRECT_INFILE = In the case of we have a infile
					  redirect STDIN in the infile
	REDIRECT_OUTFILE = In the case of we have a outfile
					   redirect STDOUT in the outfile
	REDIRECT_APPEND = In the case of we have a append
					  redirect STDOUT in the append
*/

int	setup_redirection(t_data *data, int cmd_process)
{
	t_exec_redir	*current;

	current = data->exec->t_exec_redir;
    if (cmd_process > 0 && data->old_read_pipe != -1)
    {
        dup2(data->old_read_pipe, STDIN_FILENO);
        close(data->old_read_pipe);
    }
    if (cmd_process < data->nbr_of_command - 1)
    {
        dup2(data->current_pipe[1], STDOUT_FILENO);
		close(data->current_pipe[0]);
		close(data->current_pipe[1]);
    }
	while (current != NULL)
	{
		if (redirect_infile(data, current) == -1)
			return (-1);
		if (redirect_outfile(data, current) == -1)
			return (-1);
		if (redirect_append(data, current) == -1)
			return (-1);
		redirect_heredoc(data, current);
		current = current->next;
	}
    return (0);
}
