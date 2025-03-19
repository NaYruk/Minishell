/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:11:06 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/19 21:12:33 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	error_dup_arg(t_data *data, int *size)
{
	if (!data->exec->arg_cmd[*size])
	{
		while (--(*size) >= 0)
			free(data->exec->arg_cmd[*size]);
		free(data->exec->arg_cmd);
		data->exec->arg_cmd = NULL;
		malloc_error(data);
	}
}

void	get_args_cmd(t_data *data, t_token **current)
{
	t_token	*start;
	int		size;

	start = *current;
	size = 0;
	while (*current && ((*current)->token == CMD || (*current)->token == ARG))
	{
		size++;
		*current = (*current)->next;
	}
	data->exec->arg_cmd = malloc(sizeof(char *) * (size + 1));
	if (!data->exec->arg_cmd)
		malloc_error(data);
	*current = start;
	size = 0;
	while (*current && ((*current)->token == CMD || (*current)->token == ARG))
	{
		data->exec->arg_cmd[size] = ft_strdup((*current)->line);
		error_dup_arg(data, &size);
		*current = (*current)->next;
		size++;
	}
	*current = start;
	data->exec->arg_cmd[size] = NULL;
}
