/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rafter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:23:54 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/05 22:37:57 by mmilliot         ###   ########.fr       */
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
static void	special_error(t_data *data, char *line, char *subline)
{
	ft_putstr_fd(line, 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(subline, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd("\n", 2);
	free_token(data);
	free_garbage(data);
	exit(2);
}

/*
	Error Rafter is the function for detected if an error exist :
		error : <<< >>> <<<< >>>> <<<<<< >>>>>> .....
*/

static void	error_rafter(t_data *data, int nbr, t_token *current)
{
	if (current->status == 0 && current->token > OUTFILE)
	{
		nbr = rafter_nbr(current->line, nbr);
		if (nbr < 3 && nbr >= 1)
			token_error(data, "syntax error near unexpected token `newline'\n");
		if (current->line[0] == '<')
		{
			if (nbr == 3)
				token_error(data,
					"syntax error near unexpected token `newline'\n");
			else if (nbr == 4)
				token_error(data, "syntax error near unexpected token `<'\n");
			else if (nbr == 5)
				token_error(data, "syntax error near unexpected token `<<'\n");
			else if (nbr >= 6)
				token_error(data, "syntax error near unexpected token `<<<'\n");
		}
		else
		{
			if (nbr == 3)
				token_error(data, "syntax error near unexpected token `>'\n");
			else if (nbr >= 4)
				token_error(data, "syntax error near unexpected token `>>'\n");
		}
	}
}

/*
	check_rafter =  Verify the position of each <,<<,>>,> and find any error.
	Travel the chained list until the end.
	Error Rafter is the function for detected if an error exist :
		error : <<< >>> <<<< >>>> <<<<<< >>>>>> ..... 
	If a Rafter node is not followd by an argument, it is an error.
	If the last token is a Rafter token, it is an error.
*/

void	check_rafter(t_data *data)
{
	t_token	*current;
	int		nbr;

	nbr = 0;
	current = data->lst_token;
	while (current != NULL)
	{
		error_rafter(data, nbr, current);
		if (current->token >= HEREDOC && current->token <= OUTFILE)
		{
			if (current->next != NULL)
			{
				if (current->next->token != ARG)
					special_error(data, "syntax error near unexpected token ",
						current->next->line);
			}
			else
				token_error(data,
					"syntax error near unexpected token `newline'\n");
		}
		current = current->next;
	}
}
