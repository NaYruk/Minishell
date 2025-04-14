/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:01:44 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/14 19:14:00 by mcotonea         ###   ########.fr       */
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

bool	catch_signal(t_data *data, char *line, char *delimiter, int fd)
{
    if (!line) // Si CTRL+D est détecté
    {
        if (fd != -1)
        {
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        if (g_signal != SIGINT) // Afficher le warning uniquement si ce n'est pas un SIGINT
        {
            ft_putstr_fd("\n", 2);
            ft_putstr_fd("warning: here-document delimited by EOF. Wanted: '", 2);
            ft_putstr_fd(delimiter, 2);
            ft_putstr_fd("'.\n", 2);
        }
        return (true);
    }
    if (g_signal == SIGINT) // Si SIGINT est détecté
    {
        if (fd != -1)
        {
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        update_exit_status(data);
        return (true);
    }
    return (false);
}

/* bool	catch_signal(t_data *data, char *line, char *delimiter, int fd)
{
	if (!line || g_signal == SIGINT)
	{
		if (fd != -1)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (!line && g_signal != SIGINT)
		{
			ft_putstr_fd("\n", 2);
			ft_putstr_fd("warning: here-document delimited by EOF. Wanted: '", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("'.\n", 2);
		}
		if (g_signal == SIGINT)
			update_exit_status(data);
		return (true);
	}
	return (false);
} */

void	read_heredoc_to_pipe(t_data *data, int write_pipe, t_token *current)
{
	t_token	*heredoc_token;
	char	*line;
	char	*delimiter;
	int		fd;
	
	heredoc_token = current;
	delimiter = current->line;
	line = NULL;
	setup_signals_heredoc();
	fd = open("/dev/tty", O_RDONLY);
	g_signal = 0;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = ft_strtrim(line = get_next_line(STDIN_FILENO), "\n");
		if (catch_signal(data, line, delimiter, fd) == true)
		{
			if (!line)
				break;
			return;
		}
			return ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return ;
		}
		ft_putstr_fd(line, write_pipe);
		ft_putstr_fd("\n", write_pipe);
		free(line);
	}
}

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
void	malloc_heredoc_fd(t_data *data, int nbr)
{
	int	i;
	
	i = 0;
	if (nbr == 0)
		return ;
	data->heredoc_fd = malloc(sizeof(int *) * nbr);
	if (!data->heredoc_fd)
		malloc_error(data);
	add_g_c_node(data, &data->g_c, (void **)data->heredoc_fd, false);
	while (i != nbr)
	{
		data->heredoc_fd[i] = malloc(sizeof(int) * 2);
		if (!data->heredoc_fd[i])
			malloc_error(data);
		add_g_c_node(data, &data->g_c, (void **)data->heredoc_fd[i], false);
		if (pipe(data->heredoc_fd[i]) == -1)
			error(data, "PIPE");
		i++;
	}
	return ;
}

void	close_fd(t_data *data, int hd_index)
{
	while (hd_index > 0)
	{
		close (data->heredoc_fd[hd_index][0]);
		close (data->heredoc_fd[hd_index][1]);
		hd_index--;
	}
}

int	exec_heredoc2(t_data *data, t_token *current, int tmp[2])
{
	int		hd_index;
	bool	heredoc_detected_in_pipe;
	
	hd_index = 0;
	heredoc_detected_in_pipe = false;
	while (current != NULL)
	{
		if (current->token == HEREDOC && current->next && current->next->token == ARG)
		{
			if (heredoc_detected_in_pipe)
				close(tmp[0]);
			if (pipe(tmp) == -1)
				error(data, "PIPE");
			read_heredoc_to_pipe(data, tmp[1], current->next);
			close(tmp[1]);
			if (g_signal == SIGINT)
			{
				close(tmp[0]);
				close_fd(data, hd_index);
                return (1);
			}
			heredoc_detected_in_pipe = true;
			setup_signals_interactive();
		}
		if (current->token == PIPE || !current->next)
		{
			if (heredoc_detected_in_pipe)
			{
				data->heredoc_fd[hd_index][0] = tmp[0];
				close(data->heredoc_fd[hd_index][1]);
                hd_index++;
			}
			heredoc_detected_in_pipe = false;
		}
		current = current->next;
	}
	return (0);
}

int	exec_heredoc(t_data *data)
{
	t_token	*current;
	int		nbr_heredoc;
	int		tmp[2];
	
	nbr_heredoc = nbr_of_heredoc(data);
	if (nbr_heredoc == 0)
		return (0);
	current = data->lst_token;
	malloc_heredoc_fd(data, nbr_heredoc);
	if (exec_heredoc2(data, current, tmp) == 1)
	{
		g_signal = 0;
		return (-1);
	}
	return (0);
}
