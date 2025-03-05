/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:37:32 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/05 22:39:29 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	if detected a < << do infile function
	- While the line contain | Just count
	- Set data->operator in true keep in mind that the next node
		to store is an operator to stop traversing the string.
	- Malloc the operator token
*/

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

/* 
	if detected a > >> do outfile function
	- While the line contain | Just count
	- Set data->operator in true keep in mind that the next node
		to store is an operator to stop traversing the string.
	- Malloc the operator token
*/

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

/* 
	if detected a | do pipe function
	- While the line contain | Just count
	- Set data->operator in true keep in mind that the next node
		to store is an operator to stop traversing the string.
	- Malloc the operator token
*/

int	pipes(t_data *data, int *i, int *count)
{
	while (data->prompt[*i] == '|')
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

/* Function for find an operator */

bool	operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

/* 
	Operator function for find an operator in the prompt :
	an Operator is : < > << >> | ||
	infile = < <<
	outfile = > >> 
	pipe = | ||
	if detected a < do infile function
	if detected a > do outfile function
	if detected a | do pipe function
	Each function set all data for recognize the operator
	in the cut line function.
	In this part we can have ||||||||||||||| or <<<<<<<<
	in a token.
*/

int	is_operator(t_data *data, int *i)
{
	int	count;

	count = 0;
	if (ft_strncmp(&data->prompt[*i], "<", 1) == 0)
		return (infile(data, i, &count));
	else if (ft_strncmp(&data->prompt[*i], ">", 1) == 0)
		return (outfile(data, i, &count));
	else if (ft_strncmp(&data->prompt[*i], "|", 1) == 0)
		return (pipes(data, i, &count));
	return (0);
}
