/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:01:44 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/09 23:36:01 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

void	read_heredoc_to_pipe(t_data *data, int write_pipe, t_token *current)
{
	char	*line;
	char	*delimiter;
	t_token	*heredoc_token;
	int		fd;
	setup_signals_heredoc();
	line = NULL;
	delimiter = current->line;
	heredoc_token = current;
	fd = open("/dev/tty", O_RDONLY);
	while (1)
	{
		if (g_signal == SIGINT)
		{
			if (fd != -1)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			data->exec_heredoc = 1;
			update_exit_status(data);
			break ;
		}
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		line = ft_strtrim(line, "\n");
		if (!line)
		{
			if (fd != -1)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			if (g_signal != SIGINT)
			{
				ft_putstr_fd("\n", 2);
				ft_putstr_fd("warning: here-document delimited by EOF. Wanted: '", 2);
				ft_putstr_fd(delimiter, 2);
				ft_putstr_fd("'.\n", 2);
			}
			break ;
		}
		else if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, write_pipe);
		ft_putstr_fd("\n", write_pipe);
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
		error(data, "PIPE");
	read_heredoc_to_pipe(data, pipefd[1], current);
	close(pipefd[1]);
	if (g_signal == SIGINT)
	{
		close(pipefd[0]);
		return (-1);
	}
	setup_signals_interactive();
	if (data->exec->last_heredoc_fd != -1)
		close(data->exec->last_heredoc_fd);
	data->exec->last_heredoc_fd = pipefd[0];
	return (0);
}
