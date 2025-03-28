/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:21:16 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/28 01:40:14 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

/* Function for write a token error */

int	token_error(t_data *data, char *line)
{
	ft_putstr_fd(line, 2);
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
			return (token_error(data, "syntax error near unexpected token `|'\n"));
		nbr = pipes_nbr(token->line, nbr);
		if (nbr == 2)
			return (token_error(data, "2 Pipes, we don't do bonus !\n"));
		if (nbr >= 2)
			return (token_error(data, "syntax error near unexpected token `||'\n"));
	}
	return (0);
}

int	check_potential_errors(t_data *data, int nbr, t_token *current)
{
	if (nbr > 1)
	{
		if (nbr == 2)
			return (token_error(data, "2 Pipes, we don't do bonus !\n"));
		if (nbr == 3)
			return (token_error(data,
					"syntax error near unexpected token `|'\n"));
		if (nbr >= 4)
			return (token_error(data,
					"syntax error near unexpected token `||'\n"));
	}
	if (current->next->token == PIPE && current->token == PIPE)
		return (token_error(data,
				"syntax error near unexpected token `|'\n"));
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
int	check_pipes(t_data *data)
{
	t_token	*current;
	int		nbr;

	nbr = 0;
	current = data->lst_token;
	if (check_first_and_last_node(current, data) == -1)
		return (-1);
	while (current->next != NULL)
	{
		if (current->quote_char == '\0')
		{
			nbr = pipes_nbr(current->line, nbr);
			if (check_potential_errors(data, nbr, current) != 0)
				return (-1);
		}
		current = current->next;
	}
	if (check_first_and_last_node(current, data) == -1)
		return (-1);
	return (0);
}
