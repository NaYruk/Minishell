/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:23:42 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/31 11:45:55 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_append_array(t_data *data, t_token *current, int *j)
{
	int	fd_file;
	
	fd_file = 0;
	if (current->token == APPEND && (current->next->token) == ARG)
	{
		data->exec->append[(*j)++] = current->next->line;
		if (current->next->line != NULL)
		{
			fd_file = open(current->next->line,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_file == -1)
			{
				perror(current->next->line);
				data->exit_status = 1;
				return (-1);
			}
			close(fd_file);
		}
	}
	return (0);
}

int	set_outfile_array(t_data *data, t_token *current, int *k)
{
	int	fd_file;
	
	fd_file = 0;
	if (current->token == OUTFILE && (current->next->token) == ARG)
	{
		data->exec->outfile[(*k)++] = current->next->line;
		fd_file = open(current->next->line,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_file == -1)
		{
			perror(current->next->line);
			data->exit_status = 1;
			return (-1);
		}
		close(fd_file);
	}
	return (0);
}

int	set_infile_heredoc_array(t_data *data, t_token *current, int *i, int *l)
{	
	if (current->token == HEREDOC && (current->next->token) == ARG)
		data->exec->heredoc[(*l)++] = current->next->line;
	if (current->token == INFILE && (current->next->token) == ARG)
	{
		data->exec->infile[(*i)++] = current->next->line;
		if (access(current->next->line, F_OK | R_OK) == - 1)
		{
			perror(current->next->line);
			data->exit_status = 1;
			return (-1);
		}
	}
	return (0);
}

static int	malloc_redir_exec(t_data *data)
{
	data->exec->infile = ft_calloc((data->exec->nbr_infile + 1), sizeof(char *));
	if (!data->exec->infile)
		return (-1);
	data->exec->outfile = ft_calloc((data->exec->nbr_outfile + 1), sizeof(char *));
	if (!data->exec->outfile)
		return (-1);
	data->exec->append = ft_calloc(data->exec->nbr_append + 1, sizeof(char *));
	if (!data->exec->append)
		return (-1);
	data->exec->heredoc = ft_calloc(data->exec->nbr_heredoc + 1, sizeof(char *));
	if (!data->exec->heredoc)
		return (-1);
	return (0);
}

int	get_nbr_redir(t_data *data, t_token *current)
{
	data->exec->nbr_append = 0;
	data->exec->nbr_infile = 0;
	data->exec->nbr_outfile = 0;
	data->exec->nbr_heredoc = 0;
	while (current != NULL)
	{
		if (current->token == PIPE)
			break ;
		if (current->token == INFILE && current->next->token == ARG)
			data->exec->nbr_infile++;
		if (current->token == APPEND && (current->next->token) == ARG)
			data->exec->nbr_append++;
		if (current->token == OUTFILE && (current->next->token == ARG))
			data->exec->nbr_outfile++;
		if (current->token == HEREDOC && (current->next->token == ARG))
			data->exec->nbr_heredoc++;
		current = current->next;
	}
	if (malloc_redir_exec(data) == -1)
		return (-1);
	return (0);
}
