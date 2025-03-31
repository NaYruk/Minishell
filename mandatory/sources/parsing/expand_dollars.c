/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 02:07:37 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/31 18:17:36 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	GET_EXPAND_LINE :
	Extracts variable name after $ sign
	Returns substring with valid variable characters (alphanumeric + underscore)
*/

char	*get_expand_line(char *line, int *i)
{
	int		count;
	char	*line_expand;

	line_expand = NULL;
	count = *i;
	while (line[count] && (line[count] == '_' || ft_isalnum(line[count])))
		count++;
	line_expand = ft_strndup(&(line[*i]), count - *i);
	*i = count;
	return (line_expand);
}

/*
	COUNT_DOLLARS :
	Counts consecutive $ symbols and advances position
	Used to determine if expansion should occur (odd count) or not (even count)
*/

void	count_dollars(t_data *data, char *prompt, char **new_line, int *i, int *dollar_count)
{
	while (prompt[*i] == '$')
	{
		(*dollar_count)++;
		(*i)++;
	}
	if (data->classic_or_hd_expand == 1)
	{
		if (*dollar_count % 2 == 1)
		{
		if(prompt[*i - *dollar_count] == '$'
			&& (prompt[*i + 1 - *dollar_count] == SIMPLE_QUOTES
				|| prompt[*i + 1 - *dollar_count] == DOUBLE_QUOTES
				|| prompt[*i + 1 - *dollar_count] == '\0'))
			*new_line = ft_strjoin(*new_line, "$");
		}
		data->classic_or_hd_expand = 0;
	}
}

/*
	CHECK_DOLLAR_INTERROGATION :
	Checks if the current position in the prompt is followed by a '?'
	If true, expands to the exit status of the last executed command
	Updates the new line with the exit status and frees allocated memory
*/

int	check_dollar_interrogation(t_data *data,
		char **new_line, char *old_line, int *i)
{
	char	*after_expand;

	after_expand = NULL;
	if (data->prompt[*i + 1] && data->prompt[*i + 1] == '?')
	{
		after_expand = ft_itoa(data->exit_status);
		*new_line = ft_strjoin(*new_line, after_expand);
		*i += 2;
		if (after_expand)
		{
			free(old_line);
			free(after_expand);
			after_expand = NULL;
		}
		return (1);
	}
	return (0);
}

/*
	DOLLAR_EVER_OR_ODD :
	Determines whether to expand environment variables
	based on the count of $ symbols
	If the count is odd, attempts to expand the variable using ft_getenv
	If the count is even, appends the original line without expansion
*/

void	dollar_ever_or_odd(t_data *data, char **new_line,
		char *line_to_expand, int dollar_count)
{
	char	*after_expand;

	after_expand = NULL;
	if (dollar_count % 2 == 1)
	{
		after_expand = ft_getenv(data, line_to_expand, NULL);
		if (after_expand)
			*new_line = ft_strjoin(*new_line, after_expand);
	}
	else
		*new_line = ft_strjoin(*new_line, line_to_expand);
}
/*
	IF_DOLLAR :
	Handles variable expansion for $ symbols
	Expands variables with odd number of $, preserves even number of $
*/

void	if_dollar(t_data *data, char **new_line, char *prompt, int *i)
{
	char	*line_to_expand;
	char	*after_expand;
	char	*old_line;
	int		dollar_count;

	line_to_expand = NULL;
	after_expand = NULL;
	dollar_count = 0;
	if (prompt[*i] == '$' && !data->simple_q)
	{
		old_line = *new_line;
		if (check_dollar_interrogation(data, new_line, old_line, i) == 1)
			return ;
		count_dollars(data, prompt, new_line, i, &dollar_count);
		line_to_expand = get_expand_line(prompt, i);
		dollar_ever_or_odd(data, new_line, line_to_expand, dollar_count);
		if (after_expand)
			free(old_line);
		free(line_to_expand);
	}
}
