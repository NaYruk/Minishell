/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:24:31 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/13 16:16:11 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	stock_char(char **new_line, char c)
{
	char	*old_line;
	char	character[2];

	character[0] = c;
	character[1] = '\0';
	old_line = *new_line;
	*new_line = ft_strjoin(old_line, character);
	free(old_line);
}

void	stock_quotes(t_data *data, int i, char **line, char **new_line)
{
	if ((*line)[i] == SIMPLE_QUOTES && !data->double_q)
	{
		data->simple_q = !data->simple_q;
		stock_char(new_line, SIMPLE_QUOTES);
	}
	else if ((*line)[i] == DOUBLE_QUOTES && !data->simple_q)
	{
		data->double_q = !data->double_q;
		stock_char(new_line, DOUBLE_QUOTES);
	}
	return ;
}
/*
	REPLACE_DOLLARS :
	Main function for environment variable expansion
	Replaces $ variables with their values while respecting quote contexts
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
			stock_char(&new_line, (*line)[i]);
		i++;
	}
	free (*line);
	*line = new_line;
}
