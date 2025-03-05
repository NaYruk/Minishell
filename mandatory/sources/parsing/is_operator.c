/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:37:32 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/05 21:00:55 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	infile(t_data *data, int *i, int *count)
{
	while (data->prompt[*i] == '<')
	{
		(*count)++;
		(*i)++;
	}
	(*i) -= *count;
	data->operator = true;
	data->name_op = ft_strndup(&data->prompt[*i], *count);
	if (!data->name_op)
		malloc_error(data);
	(*i) += *count;
	return (1);
}

int	outfile(t_data *data, int *i, int *count)
{
	while (data->prompt[*i] == '>')
	{
		(*count)++;
		(*i)++;
	}
	(*i) -= *count;
	data->operator = true;
	data->name_op = ft_strndup(&data->prompt[*i], *count);
	if (!data->name_op)
		malloc_error(data);
	(*i) += *count;
	return (1);
}

int	is_operator(t_data *data, int *i)
{
	int	count;

	count = 0;
	if (ft_strncmp(&data->prompt[*i], "<", 1) == 0)
		return (infile(data, i, &count));
	else if (ft_strncmp(&data->prompt[*i], ">", 1) == 0)
		return (outfile(data, i, &count));
	else if (ft_strncmp(&data->prompt[*i], "|", 1) == 0)
	{
		while (data->prompt[*i] == '|')
		{
			count++;
			(*i)++;
		}
		(*i) -= count;
		data->operator = true;
		data->name_op = ft_strndup(&data->prompt[*i], count);
		if (!data->name_op)
			malloc_error(data);
		(*i) += count;
		return (1);
	}
	return (0);
}

bool	operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}
