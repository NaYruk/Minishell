/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:23:42 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/25 23:30:43 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

void	set_infile_append_array(t_data *data, t_token *current, int *i, int *j)
{
	if (current->token == INFILE && (current->next->token) == ARG)
		data->exec->infile[(*i)++] = current->next->line;
	if (current->token == APPEND && (current->next->token) == ARG)
		data->exec->append[(*j)++] = current->next->line;
	return ;
}

void	set_outfile_heredoc_array(t_data *data, t_token *current, int *k, int *l)
{
	if (current->token == OUTFILE && (current->next->token) == ARG)
		data->exec->outfile[(*k)++] = current->next->line;
	if (current->token == HEREDOC && (current->next->token) == ARG)
		data->exec->heredoc[(*l)++] = current->next->line;
	return ;
}

static int	malloc_redir_exec(t_data *data)
{
	data->exec->infile = malloc(sizeof(char *) * (data->exec->nbr_infile + 1));
	if (!data->exec->infile)
		return (-1);
	data->exec->outfile = malloc(sizeof(char *) * (data->exec->nbr_outfile + 1));
	if (!data->exec->outfile)
		return (-1);
	data->exec->append = malloc(sizeof(char *) * (data->exec->nbr_append + 1));
	if (!data->exec->append)
		return (-1);
	data->exec->heredoc = malloc(sizeof(char *) * (data->exec->nbr_heredoc + 1));
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
