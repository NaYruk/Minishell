/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_the_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:27:27 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/25 02:09:46 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	quotes(char c)
{
	if (c == SIMPLE_QUOTES || c == DOUBLE_QUOTES)
		return (1);
	return (0);
}

static void	get_interior_of_quotes(t_data *data, int *i, int *count)
{
	char	type_quote;

	type_quote = '\0';
	if (quotes(data->prompt[*i]))
	{
		if (data->prompt[*i] == SIMPLE_QUOTES)
			type_quote = SIMPLE_QUOTES;
		else
			type_quote = DOUBLE_QUOTES;
	}
	(*i)++;
	while (data->prompt[*i] && data->prompt[*i] != type_quote)
	{
		(*count)++;
		(*i)++;
	}
}

static void	get_nbr_char_line(t_data *data, int *i, int *count, char **line)
{
	*count = 0;
	while (data->prompt[*i] && ft_is_white_spaces(data->prompt[*i])
		&& !quotes(data->prompt[*i]))
		(*i)++;
	if (data->prompt[*i] && !quotes(data->prompt[*i]))
		if (is_operator(data, i, line))
			return ;
	while (data->prompt[*i] && !ft_is_white_spaces(data->prompt[*i]))
	{
		if (quotes(data->prompt[*i]))
			get_interior_of_quotes(data, i, count);
		else
		{
			if (operator(data->prompt[*i]))
				break ;
			(*count)++;
		}
		(*i)++;
	}
}

static void	stock_quotes(t_data *data, int *i, char *line, int *line_index)
{
	char	type_quote;

	type_quote = '\0';
	if (quotes(data->prompt[*i]))
	{
		if (data->prompt[*i] == SIMPLE_QUOTES)
			type_quote = SIMPLE_QUOTES;
		else
			type_quote = DOUBLE_QUOTES;
	}
	(*i)++;
	while (data->prompt[*i] && data->prompt[*i] != type_quote)
	{
		line[(*line_index)++] = data->prompt[*i];
		(*i)++;
	}
}

static void	stock_line_in_token(t_data *data, int *i, int *count, char *line)
{
	int	line_index;

	line_index = 0;
	line = malloc(sizeof(char) * (*count + 1));
	if (!line)
		malloc_error(data);
	while (data->prompt[*i] && ft_is_white_spaces(data->prompt[*i])
		&& !quotes(data->prompt[*i]))
		(*i)++;
	while (data->prompt[*i] && !ft_is_white_spaces(data->prompt[*i]))
	{
		if (quotes(data->prompt[*i]))
			stock_quotes(data, i, line, &line_index);
		else
		{
			if (operator(data->prompt[*i]))
				break ;
			line[line_index++] = data->prompt[*i];
		}
		(*i)++;
	}
	line[line_index] = '\0';
	add_new_token(data, &data->lst_token, line);
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
	int		i;
	int		count;
	int		i_start;

	count = 0;
	i = 0;
	line = NULL;
	while ((size_t)i < ft_strlen(data->prompt))
	{
		i_start = i;
		get_nbr_char_line(data, &i, &count, &line);
		if (data->operator == false && count != 0)
		{
			i = i_start;
			stock_line_in_token(data, &i, &count, line);
		}
		if (data->operator == true)
		{
			data->operator = false;
			add_new_token(data, &data->lst_token, line);
		}
	}
	return (0);
}
