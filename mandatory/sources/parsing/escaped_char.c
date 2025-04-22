/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaped_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:04:00 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/17 18:01:15 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** char_stock:
** - This helper function updates the escaped_line buffer
**		with a specific character.
** - Advances the start index by 2 to skip the escape sequence.
** - Increments the buffer index to prepare for the next character.
*/

static void	char_stock(int *start, char **escaped_line, int *index, char c)
{
	(*start) += 2;
	(*escaped_line)[*index] = c;
	(*index)++;
	return ;
}

/*
** stock_escaped_char:
** - This function processes escaped characters in a string.
** - It identifies escape sequences (e.g., \n, \t) and
**		replaces them with their corresponding characters.
** - Updates the escaped_line buffer with the processed characters.
** - Advances the start index and increments the buffer index accordingly.
*/

void	stock_escaped_char(char *line, int *start,
			char **escaped_line, int *index)
{
	char	*old_line;

	if (line[*start] == '\\' && line[*start + 1] == 'a')
		char_stock(start, escaped_line, index, '\a');
	else if (line[*start] == '\\' && line[*start + 1] == 'b')
		char_stock(start, escaped_line, index, '\b');
	else if (line[*start] == '\\' && line[*start + 1] == 't')
		char_stock(start, escaped_line, index, '\t');
	else if (line[*start] == '\\' && line[*start + 1] == 'n')
		char_stock(start, escaped_line, index, '\n');
	else if (line[*start] == '\\' && line[*start + 1] == 'v')
		char_stock(start, escaped_line, index, '\v');
	else if (line[*start] == '\\' && line[*start + 1] == 'f')
		char_stock(start, escaped_line, index, '\f');
	else if (line[*start] == '\\' && line[*start + 1] == 'r')
		char_stock(start, escaped_line, index, '\r');
	else
	{
		old_line = *escaped_line;
		*escaped_line = ft_strjoin(*escaped_line, &line[(*start)++]);
		free(old_line);
		(*index)++;
	}
}

/*
** check_escaped_content:
** - This function processes a segment of a string enclosed in single quotes,
**		handling escaped characters.
** - It identifies and converts escaped sequences (e.g., \n, \t)
**		into their corresponding characters.
** - Builds a new string with the processed content,
**		preserving the single quotes around it.
** - Updates the original string and index to reflect the processed content.
*/

void	check_escaped_content(t_data *data, char **line,
			int *i, char **new_line)
{
	t_escaped_char	e_c;

	ft_memset(&e_c, 0, sizeof(t_escaped_char));
	e_c.start = *i + 2;
	e_c.end = e_c.start;
	while ((*line)[e_c.end] && (*line)[e_c.end] != SIMPLE_QUOTES)
		(e_c.end)++;
	e_c.escaped_line = malloc(sizeof(char) * (e_c.end - e_c.start) + 3);
	if (!(e_c.escaped_line))
		malloc_error(data);
	ft_memset(e_c.escaped_line, 0, sizeof(char) * (e_c.end - e_c.start) + 3);
	e_c.escaped_line[(e_c.index)++] = SIMPLE_QUOTES;
	while ((*line)[e_c.start] && (*line)[e_c.start] != SIMPLE_QUOTES)
		stock_escaped_char(*line, &(e_c.start),
			&(e_c.escaped_line), &(e_c.index));
	e_c.escaped_line[(e_c.index)++] = SIMPLE_QUOTES;
	e_c.escaped_line[e_c.index] = '\0';
	e_c.old_line = *new_line;
	*new_line = ft_strjoin(e_c.old_line, e_c.escaped_line);
	if (!(*new_line))
		malloc_error(data);
	free(e_c.old_line);
	free(e_c.escaped_line);
	*i = e_c.end;
}
