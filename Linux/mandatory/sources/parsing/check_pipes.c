/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:11:00 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/15 22:49:54 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Function for write a token error */

int	token_error(t_data *data, char *line, bool newline)
{
	if (newline == true)
	{
		line = ft_strdup("syntax error near unexpected token `newline'\n");
		if (!line)
			malloc_error(data);
	}
	ft_putstr_fd(line, 2);
	if (newline == true)
		free(line);
	data->exit_status = 2;
	return (-1);
}

/* Function for count the number of pipe in a line */

static int	pipes_nbr(char *line, int nbr)
{
	int	i;

	nbr = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|')
			nbr++;
		i++;
	}
	return (nbr);
}

/*
	IF the first or last node is an | it is an error ! this is the function
	of the check_first_and_last_node function.
*/

static int	check_first_and_last_node(t_token *token, t_data *data)
{
	int		nbr;

	nbr = 0;
	if (token->quote_char == '\0')
	{
		if (token->token == PIPE)
			return (token_error
				(data, "syntax error near unexpected token `|'\n", 0));
		nbr = pipes_nbr(token->line, nbr);
		if (nbr == 2)
			return (token_error(data, "2 Pipes, we don't do bonus !\n", 0));
		if (nbr >= 2)
			return (token_error
				(data, "syntax error near unexpected token `||'\n", 0));
	}
	return (0);
}

/*
** check_potential_errors:
** - This function checks for syntax errors related to pipe tokens (`|`).
** - Validates the number of consecutive pipes and returns an error if invalid.
** - Handles specific cases for single, double, or multiple consecutive pipes.
** - Ensures that two consecutive pipe tokens are not allowed in the token list.
*/

int	check_potential_errors(t_data *data, int nbr, t_token *current)
{
	if (nbr > 1)
	{
		if (nbr == 2)
			return (token_error(data, "2 Pipes, we don't do bonus !\n", 0));
		if (nbr == 3)
			return (token_error(data,
					"syntax error near unexpected token `|'\n", 0));
		if (nbr >= 4)
			return (token_error(data,
					"syntax error near unexpected token `||'\n", 0));
	}
	if (current->next->token == PIPE && current->token == PIPE)
		return (token_error(data,
				"syntax error near unexpected token `|'\n", 0));
	return (0);
}

/* 
	check_pipes = Verify the position of each | and find any error.
	IF the first or last node is an | it is an error ! this is the function
	of the check_first_and_last_node function.
	Travel the chained list until the end.
	IN THE STRUCT TOKEN WE HAVE THE STATUS VALUE
	STATUS = 0 = NO QUOTES
	STATUS = 1 = SIMPLE QUOTES
	STATUS = 2 = DOUBLE QUOTES
	we have several error for the pipes, dependinf on the number of pipes.
*/
int	check_pipes(t_data *data, t_token *current)
{
	int		nbr;

	nbr = 0;
	if (current != NULL)
	{
		if (!current->prev || !current->next)
		{
			if (check_first_and_last_node(current, data) == -1)
				return (-1);
		}
		else if (current->quote_char == '\0')
		{
			nbr = pipes_nbr(current->line, nbr);
			if (check_potential_errors(data, nbr, current) != 0)
				return (-1);
		}
	}
	return (0);
}

// check les node dans l ordre, remanier les fonctions pour faire
//node par node avec un current mobile.