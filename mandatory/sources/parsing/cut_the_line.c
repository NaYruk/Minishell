/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_the_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:27:27 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/21 15:14:39 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* save_quotes : function for saves the value of the opening quote " or ' */

static void	save_quotes(t_data *data, int *i, int *quote, char *quote_char)
{
	if (data->prompt[*i] == SIMPLE_QUOTES || data->prompt[*i] == DOUBLE_QUOTES)
	{
		*quote_char = data->prompt[*i];
		*quote = 1;
		(*i)++;
	}
}

/* 
	get_line : Function for separate each token and
				 stock each token node in a chained list.
	quote variable is for indicate if a open quote is detected.
	- Skip the Whitespaces.
	- if an operator is detected,return for execute if (data->operator == true)
	- save_quotes : function for saves the value of the opening quote " or '
	- As long as there is no Whitespace or there is in the " " or ' '
		- if an operator is detected and !quote, break for execute
			if (data->operator == true)
		- if the closing quote is find, quote = 0 for marking
			the end of the quote
		- Just count the number of character to stock in the token node.
	- if the last char is the quote char, we need to i-- for get the
		exact number for the token line malloc
*/

static void	get_line(t_data *data, int *i, int *count, char *quote_char)
{
	int	quote;

	quote = 0;
	while ((ft_is_white_spaces(data->prompt[*i]) && data->prompt[*i]) && !quote)
		(*i)++;
	if ((data->prompt[*i]) && !quote)
		if (is_operator(data, i))
			return ;
	save_quotes(data, i, &quote, quote_char);
	*count = 0;
	while (data->prompt[*i]
		&& (quote || !ft_is_white_spaces(data->prompt[*i])))
	{
		if (operator(data->prompt[*i]) && !quote)
			break ;
		if (*quote_char == data->prompt[*i] && quote)
			quote = 0;
		(*i)++;
		(*count)++;
	}
	if (data->prompt[*i - 1] == *quote_char)
	{
		(*count)--;
		(*i)--;
	}
}

/* 
   Function for stock the line cut in a new token node
   and add this token to the chained list
   we skip the closing quote if it exists.
*/

static void	stock_the_line(t_data *data, char *line, int *i, char quote_char)
{
	if (line[0] != '\0')
	{
		if (data->prompt[*i] == quote_char)
			(*i)++;
		if (!line)
			malloc_error(data);
		add_new_token(data, &data->lst_token, line, quote_char);
	}
	return ;
}

/*
	Cut_the_line = Function for Cut the line in token :
		arg, cmd, and, or, pipe, outfile, append, infile, heredoc
	- check_quotes : In this function we search if a quote is remain open in
					 this case, we have a error message.
	- While the Prompt contain any character, we parcour the line.
	
	- get_line : Function for separate each token and
				 stock each token node in a chained list.
	a TOKEN IS : part of the prompt line associated
				 with its function at runtime.
	- IF OPERATOR IS FALSE : If there is no operator in the actual
							   line cut, just stock this part of the prompt
							   in line variable and stock_the line in the node.
	- IF OPERATOR IS TRUE : If the actual line cut is an operator, jsut stock
							the operator in a new node and add this node in the
							chained list.
*/

int	cut_the_line(t_data *data)
{
	char	*line;
	char	quote_char;
	int		i;
	int		count;

	count = 0;
	i = 0;
	quote_char = '\0';
	if (check_quotes(data, data->prompt) == -1)
		return (-1);
	while ((size_t)i < ft_strlen(data->prompt))
	{
		get_line(data, &i, &count, &quote_char);
		if (data->operator == false)
		{
			line = ft_strndup(&data->prompt[i - count], count);
			stock_the_line(data, line, &i, quote_char);
		}
		if (data->operator == true)
		{
			data->operator = false;
			add_new_token(data, &data->lst_token, data->name_op, quote_char);
		}
	}
	return (0);
}
