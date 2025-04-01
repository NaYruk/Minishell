/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:04:12 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/01 21:35:20 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_exec(t_data *data)
{
	data->exec = malloc(sizeof(t_exec));
	if (!data->exec)
		malloc_error(data);
	add_g_c_node(data, &data->g_c, (void **)data->exec, false);
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
	if ((*current)->token == CMD)
	{
		get_args_cmd(data, *current);
		if (get_cmd_path(data, current) == -1)
			return (-1);
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
	data->exec->heredoc[0] = NULL;
	if ((*current)->token == PIPE)
		*current = (*current)->next;
	while (*current != NULL)
	{
		if ((*current)->token == PIPE)
		{
			*current = (*current)->next;
			break ;
		}
		if (args_and_cmd(data, current) == -1)
			return (-1);
		if (set_infile_heredoc_array(data, *current, &i, &j) == -1)
			return (-1);
		if (set_outfile_array(data, *current, &k) == -1)
			return (-1);
		if (set_append_array(data, *current, &j) == -1)
			return (-1);
		if (data->exec->heredoc[0] != NULL && (*current)->token == HEREDOC)
			if (exec_heredoc(data) == -1)
				return (-1);
		*current = (*current)->next;
	}
	data->exec->infile[i] = NULL;
	data->exec->outfile[k] = NULL;
	data->exec->append[j] = NULL;
	return (0);
}
