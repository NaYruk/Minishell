/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_the_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:27:27 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/15 20:51:37 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** get_interior_of_quotes:
** - This function processes the content inside
**		a quoted segment of the input prompt.
** - It identifies the type of quote (single or double)
**		and counts the characters within.
** - Skips the opening and closing quotes while updating the index and count.
** - Handles cases where the quote is immediately closed.
*/

static void	get_interior_of_quotes(t_data *data, int *i, int *count)
{
	char	type_quote;

	type_quote = '\0';
	if (ft_is_quote(data->prompt[*i]))
	{
		if (data->prompt[*i] == SIMPLE_QUOTES)
			type_quote = SIMPLE_QUOTES;
		else
			type_quote = DOUBLE_QUOTES;
	}
	(*i)++;
	if (data->prompt[*i] == type_quote)
	{
		(*count)++;
		return ;
	}
	while (data->prompt[*i] && data->prompt[*i] != type_quote)
	{
		(*count)++;
		(*i)++;
	}
}

/*
** get_nbr_char_line:
** - This function calculates the number of characters 
**		in a segment of the input prompt.
** - It skips whitespace and identifies operators or quoted segments.
** - Updates the count of characters and the current index in the prompt.
** - Handles escape characters and stops at operators or whitespace.
*/

static void	get_nbr_char_line(t_data *data, int *i, int *count, char **line)
{
	*count = 0;
	while (data->prompt[*i] && ft_is_white_spaces(data->prompt[*i])
		&& !ft_is_quote(data->prompt[*i]))
		(*i)++;
	if (data->prompt[*i] && !ft_is_quote(data->prompt[*i]))
		if (is_operator(data, i, line))
			return ;
	while (data->prompt[*i] && !ft_is_white_spaces(data->prompt[*i]))
	{
		if (ft_is_quote(data->prompt[*i]))
			get_interior_of_quotes(data, i, count);
		else
		{
			if (operator(data->prompt[*i]))
				break ;
			else if (data->prompt[*i] != '\\')
				(*count)++;
		}
		(*i)++;
	}
}

/*
** stock_quotes:
** - This function processes a quoted segment of the input prompt.
** - It identifies the type of quote (single or double)
**		and extracts the content inside.
** - The extracted content is stored in the provided line buffer.
** - Updates the quote character in the data structure for further processing.
*/

static void	stock_quotes(t_data *data, int *i, char *line, int *line_index)
{
	char	type_quote;

	type_quote = '\0';
	if (ft_is_quote(data->prompt[*i]))
	{
		if (data->prompt[*i] == SIMPLE_QUOTES)
		{
			type_quote = SIMPLE_QUOTES;
			data->quotes_char = SIMPLE_QUOTES;
		}
		else
		{
			type_quote = DOUBLE_QUOTES;
			data->quotes_char = DOUBLE_QUOTES;
		}
	}
	(*i)++;
	while (data->prompt[*i] && data->prompt[*i] != type_quote)
	{
		line[(*line_index)++] = data->prompt[*i];
		(*i)++;
	}
}

/*
** stock_line_in_token:
** - This function extracts segment of the input prompt and stores as a token.
** - It handles quoted strings, operators, and escape while copying characters.
** - Allocates memory for the token and adds it to the linked list of tokens.
** - Ensures proper handling of whitespace and resets
**		the quote character after processing.
*/

static void	stock_line_in_token(t_data *data, int *i, int *count, char *line)
{
	int	line_index;

	line_index = 0;
	line = malloc(sizeof(char) * (*count + 1));
	if (!line)
		malloc_error(data);
	while (data->prompt[*i] && ft_is_white_spaces(data->prompt[*i])
		&& !ft_is_quote(data->prompt[*i]))
		(*i)++;
	while (data->prompt[*i] && !ft_is_white_spaces(data->prompt[*i]))
	{
		if (ft_is_quote(data->prompt[*i]))
			stock_quotes(data, i, line, &line_index);
		else
		{
			if (operator(data->prompt[*i]))
				break ;
			if (data->prompt[*i] != '\\')
				line[line_index++] = data->prompt[*i];
		}
		(*i)++;
	}
	line[line_index] = '\0';
	add_new_token(data, &data->lst_token, line);
	data->quotes_char = '\0';
}

/*
** cut_the_line:
** - This function processes the input prompt and splits it into tokens.
** - It iterates through the prompt, identifying and extracting
**		tokens based on quotes, operators, and whitespace.
** - Tokens are stored in a linked list for further processing.
** - Handles special cases like operators and quoted strings.
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
