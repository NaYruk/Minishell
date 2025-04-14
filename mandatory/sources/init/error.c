/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:12:55 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/09 12:48:59 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** malloc_error:
** - This function handles errors related to memory allocation failures.
** - Displays an error message using `perror` to indicate the malloc issue.
** - Frees allocated memory, including the execution
**		structure and garbage collector.
** - Exits the program with a failure status to prevent further execution.
*/

void	malloc_error(t_data *data)
{
	perror("Error with a malloc\n");
	if (data->exec)
		free_exec_struct(data);
	free_garbage(data);
	exit(EXIT_FAILURE);
}

/*
** error:
** - This function handles generic errors by displaying
**		an error message using `perror`.
** - Frees allocated memory, including the execution
**		structure and garbage collector.
** - Exits the program with a failure status after handling the error.
*/

void	error(t_data *data, char *error)
{
	perror(error);
	if (data->exec)
		free_exec_struct(data);
	close_heredoc_fd(data);
	free_garbage(data);
	exit(EXIT_FAILURE);
}

/*
** ft_error_name:
** - This function displays an error message for invalid
**		identifiers in the `export` command.
** - Formats the error message to include
**		the invalid identifier in single quotes.
** - Outputs the error message to the standard error (file descriptor 2).
*/

void	ft_error_name(char *str)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

/*
** ft_free_env:
** - This function frees all the memory allocated
**		for an environment variable array.
** - Iterates through the array, freeing each string individually.
** - Frees the array itself after all elements are released.
** - Ensures no memory leaks occur when
**		the environment array is no longer needed.
*/

void	ft_free_env(char **tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		free (tmp[i]);
		i++;
	}
	free (tmp);
	return ;
}
