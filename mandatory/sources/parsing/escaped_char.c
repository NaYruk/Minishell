/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaped_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:04:00 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/09 22:03:17 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	char_stock(int *start, char **escaped_line, int *index, char c)
{
	(*start) += 2;
	(*escaped_line)[*index] = c;
	(*index)++;
	return ;
}

void	stock_escaped_char(char *line, int *start,
			char **escaped_line, int *index)
{
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
		stock_char(escaped_line, line[(*start)++]);
		(*index)++;
	}
}

void	check_escaped_content(t_data *data, char **line,
			int *i, char **new_line)
{
	t_escaped_char	e_c;

	e_c.start = *i + 2;
	e_c.end = e_c.start;
	e_c.index = 0;
	e_c.old_line = NULL;
	e_c.escaped_line = NULL;
	while ((*line)[e_c.end] && (*line)[e_c.end] != SIMPLE_QUOTES)
		(e_c.end)++;
	e_c.escaped_line = calloc(sizeof(char) * (e_c.end - e_c.start + 3), 0);
	if (!(e_c.escaped_line))
		malloc_error(data);
	e_c.escaped_line[(e_c.index)++] = SIMPLE_QUOTES;
	while ((*line)[e_c.start] && (*line)[e_c.start] != SIMPLE_QUOTES)
		stock_escaped_char(*line, &(e_c.start), &(e_c.escaped_line), &(e_c.index));
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
