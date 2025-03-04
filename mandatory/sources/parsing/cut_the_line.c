/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_the_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:27:27 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/04 13:29:03 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function for get the line = each token
	We cut the prompt by avoiding every whitespace,
	except what is included in quotes
*/

static void	get_line(t_data *data, int *i, int *count, char *quote_char)
{
	int	quote;

	quote = 0;
	while (ft_is_white_spaces(data->prompt[*i]) && data->prompt[*i] && !quote)
		(*i)++;
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
		line = ft_strndup(&data->prompt[i - count], count);
		if (data->prompt[i] == quote_char)
			i++;
		if (!line)
		{
			perror("Error with a malloc\n");
			free_garbage(data);
			exit(EXIT_FAILURE);
		}
		add_new_token_node(data, &data->lst_token, line, quote_char);
	}
	return ;
}
