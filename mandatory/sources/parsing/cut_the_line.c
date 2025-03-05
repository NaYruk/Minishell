/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_the_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:27:27 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/05 20:53:36 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	save_quotes(t_data *data, int *i, int *quote, char *quote_char)
{
	if (data->prompt[*i] == SIMPLE_QUOTES || data->prompt[*i] == DOUBLE_QUOTES)
	{
		*quote_char = data->prompt[*i];
		*quote = 1;
		(*i)++;
	}
}

static void	get_line(t_data *data, int *i, int *count, char *quote_char)
{
	int	quote;

	quote = 0;
	while ((ft_is_white_spaces(data->prompt[*i]) && data->prompt[*i]) && !quote)
		(*i)++;
	if ((data->prompt[*i]) && !quote)
		if (is_operator(data, i))
			return ;
	save_quotes(data, i, &quote, quote_char);
	*count = 0;
	while (data->prompt[*i]
		&& (quote || !ft_is_white_spaces(data->prompt[*i])))
	{
		if (operator(data->prompt[*i]) && !quote)
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

static void	stock_the_line(t_data *data, char *line, int *i, char quote_char)
{
	if (line[0] != '\0')
	{
		if (data->prompt[*i] == quote_char)
			(*i)++;
		if (!line)
			malloc_error(data);
		add_new_token(data, &data->lst_token, line, quote_char);
	}
	return ;
}

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
			stock_the_line(data, line, &i, quote_char);
		}
		if (data->operator == true)
		{
			data->operator = false;
			add_new_token(data, &data->lst_token, data->name_op, quote_char);
		}
	}
	return ;
}
