/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:23:42 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/03 14:30:00 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	set_outfile(t_data *data, t_token *current)
{
	int	fd_file;
	
	fd_file = 0;
	if (current->token == OUTFILE && (current->next->token) == ARG)
	{
		add_new_redir_node(data, &data->exec->t_exec_redir, 
			current->next->line, OUTFILE);
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
	return (0);
}

int	set_infile_heredoc(t_data *data, t_token *current)
{	
	if (current->token == HEREDOC && (current->next->token) == ARG)
		add_new_redir_node(data, &data->exec->t_exec_redir, 
			current->next->line, HEREDOC);
	if (current->token == INFILE && (current->next->token) == ARG)
	{
		add_new_redir_node(data, &data->exec->t_exec_redir, 
			current->next->line, INFILE);
		if (access(current->next->line, F_OK | R_OK) == - 1)
		{
			perror(current->next->line);
			data->error_built = 1;
			data->exit_status = 1;
			return (-1);
		}
	}
	return (0);
}
