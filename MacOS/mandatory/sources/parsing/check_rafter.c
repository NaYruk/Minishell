/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rafter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:12:45 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/15 22:54:45 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Function for get the number of rafter in a line */

static int	rafter_nbr(char *line, int nbr)
{
	int	i;

	nbr = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' || line[i] == '>')
			nbr++;
		i++;
	}
	return (nbr);
}

/* Function for write this error part :
	if (current->next != NULL)
	{
		if (current->next->token != ARG)
			special_error(data, "syntax error near unexpected token ",
				current->next->line);
	}
*/
static int	special_error(t_data *data, char *subline)
{
	char	*line;

	line = ft_strdup("syntax error near unexpected token ");
	if (!line)
		malloc_error(data);
	ft_putstr_fd(line, 2);
	free(line);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(subline, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd("\n", 2);
	data->exit_status = 2;
	return (-1);
}

/* 
    check_errors:
    - This function checks for syntax errors
		related to rafter tokens (<, <<, >, >>).
    - It validates the number of consecutive rafter characters
		and returns an error if invalid.
    - Handles specific cases for '<', '<<', '<<<',
		and their corresponding '>' variations.
    - Updates the exit status and displays an appropriate
		error message if an issue is found.
*/

static int	check_errors(t_data *data, int nbr, t_token *current)
{
	if (current->line[0] == '<')
	{
		if (nbr == 3)
			return (token_error(data, NULL, 1));
		else if (nbr == 4)
			return (token_error(data,
					"syntax error near unexpected token `<'\n", 0));
		else if (nbr == 5)
			return (token_error(data,
					"syntax error near unexpected token `<<'\n", 0));
		else if (nbr >= 6)
			return (token_error(data,
					"syntax error near unexpected token `<<<'\n", 0));
	}
	else
	{
		if (nbr == 3)
			return (token_error(data,
					"syntax error near unexpected token `>'\n", 0));
		else if (nbr >= 4)
			return (token_error(data,
					"syntax error near unexpected token `>>'\n", 0));
	}
	return (0);
}

/*
	Error Rafter is the function for detected if an error exist :
		error : <<< >>> <<<< >>>> <<<<<< >>>>>> .....
*/

static int	error_rafter(t_data *data, int nbr, t_token *current)
{
	if (current->token > OUTFILE)
	{
		nbr = rafter_nbr(current->line, nbr);
		if (nbr < 3 && nbr >= 1)
			return (token_error(data, NULL, 1));
		if (check_errors(data, nbr, current) != 0)
			return (-1);
	}
	return (0);
}

/*
	check_rafter =  Verify the position of each <,<<,>>,> and find any error.
	Travel the chained list until the end.
	Error Rafter is the function for detected if an error exist :
		error : <<< >>> <<<< >>>> <<<<<< >>>>>> ..... 
	If a Rafter node is not followd by an argument, it is an error.
	If the last token is a Rafter token, it is an error.
*/

int	check_rafter(t_data *data, t_token *current)
{
	int		nbr;

	nbr = 0;
	if (current != NULL)
	{
		if (current->quote_char == '\0')
		{
			if (error_rafter(data, nbr, current) == -1)
				return (-1);
			if (current->token >= HEREDOC && current->token <= OUTFILE)
			{
				if (current->next != NULL)
				{
					if (current->next->token != ARG)
						return (special_error(data, current->next->line));
				}
				else
					return (token_error(data, NULL, 1));
			}
		}
	}
	return (0);
}
