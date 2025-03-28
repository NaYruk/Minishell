/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:04:12 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/28 04:46:49 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	data->exec->heredoc = NULL;
	data->exec->append = NULL;
	data->exec->nbr_append = 0;
	data->exec->nbr_infile = 0;
	data->exec->nbr_outfile = 0;
	data->exec->nbr_heredoc = 0;
	data->exec->last_heredoc_fd = -1;
}

int	args_and_cmd(t_data *data, t_token **current)
{
	if ((*current)->token == PIPE)
	{
		*current = (*current)->next;
		return (-1);
	}
	if ((*current)->token == CMD)
	{
		get_args_cmd(data, *current);
		get_cmd_path(data, current);
	}
	return (0);
}

int	set_exec_struct(t_data *data, t_token **current)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	if (get_nbr_redir(data, *current) == -1)
		return (-1);
	data->exec->heredoc[0] = NULL;
	if ((*current)->token == PIPE)
		*current = (*current)->next;
	while (*current != NULL)
	{
		if (args_and_cmd(data, current) == -1)
			break ;
		if (set_infile_append_array(data, *current, &i, &j) == -1)
			return (-1);
		if (set_outfile_heredoc_array(data, *current, &k, &l) == -1)
			return (-1);
		if (data->exec->heredoc[0] != NULL)
			if (exec_heredoc(data) == -1)
				return (-1);
		*current = (*current)->next;
	}
	data->exec->infile[i] = NULL;
	data->exec->outfile[k] = NULL;
	data->exec->append[j] = NULL;
	return (0);
}
