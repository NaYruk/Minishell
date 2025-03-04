/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_the_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:27:27 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/04 16:45:56 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_operator(t_data *data, int *i)
{
	if (data->prompt[*i] == '<' || data->prompt[*i] == '>' || data->prompt[*i] == '|')
	{
		data->operator = true;
		data->name_operator = ft_strndup(&data->prompt[*i], 1);
		if (!data->name_operator)
			malloc_error(data);
		(*i)++;
		return (1);
	}
	return (0);
}

int		operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}
/* 
	Function for get the line = each token
	We cut the prompt by avoiding every whitespace,
	except what is included in quotes
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
	if (data->prompt[*i] == SIMPLE_QUOTES || data->prompt[*i] == DOUBLE_QUOTES)
	{
		*quote_char = data->prompt[*i];
		quote = 1;
		(*i)++;
	}
	*count = 0;
	while (data->prompt[*i]
		&& (quote || !ft_is_white_spaces(data->prompt[*i])))
	{
		if (operator(data->prompt[*i]))
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
	Function For cut the line :
	Parameters:
  	- `data`: Pointer to `t_data` with `prompt` and token list (`lst_token`).
 
	Steps:
	1. Initializes tracking variables.
	2. Validates quotes with `check_quotes`.
	3. Iterates through `prompt`:
    	 - Updates position and count with `get_line`.
    	 - Creates token with `ft_strndup`.
    	 - Adds token to `lst_token`.
	4. Handles memory allocation errors.
*/

void	cut_the_line(t_data *data)
{
	char	*line;
	char	quote_char;
	int		i;
	int		count;

	count = 0;
	i = 0;
	quote_char = '\0';
	line = NULL;
	check_quotes(data, data->prompt);
	while ((size_t)i < ft_strlen(data->prompt))
	{
		get_line(data, &i, &count, &quote_char);
		if (data->operator == false)
		{
			line = ft_strndup(&data->prompt[i - count], count);
			if (data->prompt[i] == quote_char)
				i++;
			if (!line)
				malloc_error(data);
			add_new_token_node(data, &data->lst_token, line, quote_char);
		}
		if (data->operator == true)
		{
			data->operator = false;
			add_new_token_node(data, &data->lst_token, data->name_operator, quote_char);
		}
	}
	return ;
}
