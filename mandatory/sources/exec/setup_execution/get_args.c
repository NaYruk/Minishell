/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:11:06 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/09 16:03:48 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	error_dup_arg :
	Handles errors in duplicating command arguments.
	Checks if the duplication of an argument was unsuccessful.
	If duplication fails, frees all previously allocated
	arguments and the argument array itself.
	Sets the argument array to NULL and calls malloc_error to handle
	the memory allocation error.
*/

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

/*
	size_for_malloc :
	Calculates the number of arguments for memory allocation.
	Iterates through a linked list of tokens starting from the current token.
	Counts the number of CMD and ARG tokens
	that should be included in the argument array.
	Stops counting when a PIPE token is encountered.
	Returns the total count of arguments to be allocated.
*/

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

/*
	put_args_cmd :
	Populates the argument array for a command from a linked list of tokens.
	Iterates through the token list starting from the current token.
	Duplicates the command and argument strings from the tokens
	and assigns them to data->exec->arg_cmd.
	Stops processing when a PIPE token is encountered.
	Handles errors in duplicating arguments using error_dup_arg.
	Ensures the argument array is NULL-terminated.
*/

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

/*
	get_args_cmd :
	Allocates memory and initializes the argument array for a command.
	Determines the size needed for
	the argument array by calling size_for_malloc.
	Allocates memory for the argument array
	and assigns it to data->exec->arg_cmd.
	Calls malloc_error if memory allocation fails.
	Initializes the argument array by calling put_args_cmd
	with the current token.
*/

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
