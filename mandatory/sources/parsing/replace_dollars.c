/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:24:31 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/06 22:37:06 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/minishell.h"

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

int	check_dollar_interrogation(t_data *data, char **new_line, int *i)
{
	char	*after_expand;

	after_expand = NULL;
	if (data->prompt[*i] == '?')
	{
		after_expand = ft_itoa(data->exit_status);
		*new_line = ft_strjoin(*new_line, after_expand);
		free(after_expand);
		return (1);
	}
	return (0);
}


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

void	extand_dollar(t_data *data, char **new_line, char *prompt, int *i)
{
	char	*var_name;
	char	*after_expand;

	var_name = NULL;
	after_expand = NULL;
	(*i)++;
	if (check_dollar_interrogation(data, new_line, i) == 1)
		return ;
	else if ((ft_isalnum(prompt[*i]) || prompt[*i] == '_'))
	{
		var_name = get_expand_line(prompt, i);
		after_expand = ft_getenv(data, var_name, NULL);
		if (after_expand)
			*new_line = ft_strjoin(*new_line, after_expand);
		free(var_name);
	}
	else
		stock_char(new_line, '$');
	(*i)--;
}

int	expand_till(t_data *data, char **new_line, char *line, int *i)
{
	char	*home;
	char	*old_line;

	home = NULL;
	old_line = NULL;
	if ((line[*i + 1] == '\0' || (line[*i + 1] && (line[*i + 1] == ' ' || line[*i + 1] == '/'))) && ((*i > 0 && line[*i - 1] == ' ') || (*i == 0)))
	{
		home = ft_getenv(data, "HOME", false);
		if (!home)
		{
			data->exit_status = 0;
			return (0);
		}
		old_line = *new_line;
		*new_line = ft_strjoin(old_line, home);
		free(old_line);
	}
	else
		stock_char(new_line, line[*i]);
	return (0);
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
		if ((*line)[i] == SIMPLE_QUOTES && !data->double_q)
		{
			data->simple_q = !data->simple_q;
			stock_char(&new_line, SIMPLE_QUOTES);
		}
		else if ((*line)[i] == DOUBLE_QUOTES && !data->simple_q)
		{
			data->double_q = !data->double_q;
			stock_char(&new_line, DOUBLE_QUOTES);
		}
		else if ((*line)[i] == '$' && !data->simple_q)
			extand_dollar(data, &new_line, *line, &i);
		else if ((*line)[i] == '~' && !data->simple_q && !data->double_q)
			expand_till(data, &new_line, *line, &i);
		else
			stock_char(&new_line, (*line)[i]);
		i++;
	}
	free (*line);
	*line = new_line;
}
