/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:24:31 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/25 19:15:59 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

/*
	IF_QUOTES :
	Tracks quote state when processing characters
	Toggles single/double quote flags when quote characters are encountered
*/

void	if_quotes(char c, bool *simple_q, bool *double_q)
{
	if (c == DOUBLE_QUOTES || c == SIMPLE_QUOTES)
	{
		if (c == SIMPLE_QUOTES && !(*simple_q))
			(*simple_q) = true;
		else if (c == SIMPLE_QUOTES && (*simple_q))
			(*simple_q) = false;
		else if (c == DOUBLE_QUOTES && !(*double_q))
			(*double_q) = true;
		else if (c == DOUBLE_QUOTES && (*double_q))
			(*double_q) = false;
	}
}

/*
	STOCK_REST :
	Copies characters from input to output until next $ or end of string
	Handles literal $ inside single quotes without expansion
*/

void	stock_rest(t_data *data, char *prompt, char **new_line, int *i)
{
	int		count;
	int		i_start;
	char	*tmp;
	char	*old_line;

	count = 0;
	i_start = *i;
	tmp = NULL;
	while (prompt[*i] != '\0' && (prompt[*i] != '$' || data->simple_q))
	{
		count++;
		(*i)++;
		if_quotes(prompt[*i], &data->simple_q, &data->double_q);
	}
	if (prompt[*i] == '$' && (prompt[*i + 1] == '\0'))
		count++;
	*i = i_start;
	old_line = *new_line;
	tmp = ft_strndup(&prompt[*i], count);
	*new_line = ft_strjoin(*new_line, tmp);
	free(old_line);
	free(tmp);
	*i += count;
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

	new_line = NULL;
	i = 0;
	new_line = ft_strdup("");
	data->simple_q = false;
	data->double_q = false;
	while ((*line)[i] != '\0')
	{
		if_quotes((*line)[i], &data->simple_q, &data->double_q);
		if_dollar(data, &new_line, *line, &i);
		stock_rest(data, *line, &new_line, &i);
	}
	*line = new_line;
	return ;
}
