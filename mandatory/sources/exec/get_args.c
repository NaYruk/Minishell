/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:11:06 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/21 00:25:53 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

static int	size_for_malloc(t_token *current)
{
	int	size;

	size = 0;
	while (current)
	{
		if (current->token == PIPE)
			break ;
		if (current->token == CMD)
			size++;
		else if (current->token == ARG)
		{
			if (current->prev && (current->prev->token < 1
					|| current->prev->token > 4))
				size++;
		}
		current = current->next;
	}
	return (size);
}

static void	put_args_cmd(t_data *data, t_token *current)
{
	int	size;

	size = 0;
	while (current)
	{
		if (current->token == PIPE)
			break ;
		if (current->token == CMD || ((current->token == ARG)
				&& current->prev && (current->prev->token < 1
				|| current->prev->token > 4)))
		{
			data->exec->arg_cmd[size] = ft_strdup(current->line);
			error_dup_arg(data, &size);
			size++;
		}
		current = current->next;
	}
	data->exec->arg_cmd[size] = NULL;
}

void	get_args_cmd(t_data *data, t_token *current)
{
	t_token	*start;
	int		size;

	start = current;
	size = size_for_malloc(current);
	data->exec->arg_cmd = malloc(sizeof(char *) * (size + 1));
	if (!data->exec->arg_cmd)
		malloc_error(data);
	current = start;
	put_args_cmd(data, current);
}
