/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:04:12 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/19 21:55:22 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_exec(t_data *data)
{
	data->exec = malloc(sizeof(t_exec));
	if (!data->exec)
		malloc_error(data);
	data->exec->arg_cmd = NULL;
	data->exec->cmd_path = NULL;
	data->exec->infile = NULL;
	data->exec->outfile = NULL;
	data->exec->append = NULL;
}

static int	malloc_redir_exec(t_data *data, int nbr_infile,
	int nbr_outfile, int nbr_append)
{
	data->exec->infile = malloc(sizeof(char *) * (nbr_infile + 1));
	if (!data->exec->infile)
		return (-1);
	data->exec->outfile = malloc(sizeof(char *) * (nbr_outfile + 1));
	if (!data->exec->outfile)
		return (-1);
	data->exec->append = malloc(sizeof(char *) * (nbr_append + 1));
	if (!data->exec->append)
		return (-1);
	return (0);
}

static int	get_nbr_redir(t_data *data, t_token *current)
{
	int	nbr_infile;
	int	nbr_outfile;
	int	nbr_append;

	nbr_append = 0;
	nbr_infile = 0;
	nbr_outfile = 0;
	while (current != NULL)
	{
		if (current->token == PIPE)
			break ;
		if (current->token == INFILE && current->next->token == ARG)
			nbr_infile++;
		if (current->token == APPEND && (current->next->token) == ARG)
			nbr_append++;
		if (current->token == OUTFILE && (current->next->token == ARG))
			nbr_outfile++;
		current = current->next;
	}
	if (malloc_redir_exec(data, nbr_infile, nbr_outfile, nbr_append) == -1)
		return (-1);
	return (0);
}

int	pipes_and_cmd(t_data *data, t_token **current)
{
	if ((*current)->token == PIPE)
	{
		*current = (*current)->next;
		return (-1);
	}
	if ((*current)->token == CMD)
	{
		get_args_cmd(data, current);
		get_cmd_path(data, current);
	}
	return (0);
}

int	set_exec_struct(t_data *data, t_token **current)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	if (get_nbr_redir(data, *current) == -1)
		return (-1);
	while (*current != NULL)
	{
		if (pipes_and_cmd(data, current) == -1)
			break ;
		if ((*current)->token == INFILE && ((*current)->next->token) == ARG)
			data->exec->infile[i++] = (*current)->next->line;
		if ((*current)->token == APPEND && ((*current)->next->token) == ARG)
			data->exec->append[j++] = (*current)->next->line;
		if ((*current)->token == OUTFILE && ((*current)->next->token) == ARG)
			data->exec->outfile[k++] = (*current)->next->line;
		*current = (*current)->next;
	}
	data->exec->infile[i] = NULL;
	data->exec->outfile[k] = NULL;
	data->exec->append[j] = NULL;
	return (0);
}
