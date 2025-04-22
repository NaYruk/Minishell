/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:24:31 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/19 00:47:17 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** stock_char:
** - This function appends a single character to the `new_line` buffer.
** - Allocates memory for the updated string and frees the old buffer.
** - Ensures proper reconstruction of the input line during processing.
*/

void	stock_char(t_data *data, char **new_line, char c)
{
	char	*old_line;
	char	character[2];

	character[0] = c;
	character[1] = '\0';
	old_line = *new_line;
	*new_line = ft_strjoin(old_line, character);
	if (!(*new_line) && data)
		malloc_error(data);
	if (old_line)
		free(old_line);
}

/*
** stock_quotes:
** - This function handles the toggling of quote states
**		(single or double) in the input line.
** - Updates the `simple_q` or `double_q` flags in the
**		`t_data` structure based on the quote type.
** - Appends the quote character to the `new_line`
**		buffer for proper reconstruction of the input.
** - Ensures that single quotes are ignored inside double quotes and vice versa
*/

void	stock_quotes(t_data *data, int i, char **line, char **new_line)
{
	if ((*line)[i] == SIMPLE_QUOTES && !data->double_q)
	{
		data->simple_q = !data->simple_q;
		stock_char(data, new_line, SIMPLE_QUOTES);
	}
	else if ((*line)[i] == DOUBLE_QUOTES && !data->simple_q)
	{
		data->double_q = !data->double_q;
		stock_char(data, new_line, DOUBLE_QUOTES);
	}
	return ;
}

/*
** replace_dollars:
** - This is the main function for environment variable
**		expansion in the input line.
** - It replaces `$` variables with their corresponding
**		values while respecting quote contexts.
** - Handles special cases like `$?` for the exit status
**		and `~` for the home directory.
** - Ensures proper handling of single and double quotes
**		during the expansion process.
** - Constructs a new line with the expanded content
**		and updates the original line.
*/

void	replace_dollars(t_data *data, char **line)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = ft_strdup("");
	data->simple_q = false;
	data->double_q = false;
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '$' && (*line)[i + 1] == SIMPLE_QUOTES
			&& !data->simple_q && !data->double_q)
			check_escaped_content(data, line, &i, &new_line);
		else if (((*line)[i] == SIMPLE_QUOTES && !data->double_q)
			|| ((*line)[i] == DOUBLE_QUOTES && !data->simple_q))
			stock_quotes(data, i, line, &new_line);
		else if ((*line)[i] == '$' && !data->simple_q)
			expand_dollar(data, &new_line, *line, &i);
		else if ((*line)[i] == '~' && !data->simple_q && !data->double_q)
			expand_till(data, &new_line, *line, &i);
		else
			stock_char(data, &new_line, (*line)[i]);
		i++;
	}
	free (*line);
	*line = new_line;
}
