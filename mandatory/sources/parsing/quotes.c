/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:14:20 by mcotonea          #+#    #+#             */
/*   Updated: 2025/02/28 18:49:41 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Function for check if a Quote is detected */

int	ft_is_quote(char c)
{
	if (c == SIMPLE_QUOTES || c == DOUBLE_QUOTES)
		return (true);
	return (false);
}
/* 
	Function for check if a Whitespace is detected in the current character
*/

int	ft_is_white_spaces(char c)
{
	if (c == 32 || (c >= 7 && c <= 13))
		return (1);
	return (0);
}

/* Function to check if string contains simple_quote or double_quotes.
   If str contains quotes, check if the following character is a closed quote.
   If there is a closed quote, skip the 2 characters.
   Otherwise, increment a single or double quote counter.
   At the end of str, if the counter is even -> return true.
						if the counter is odd -> return false and display
						an error message.
*/

int	check_quotes(t_data *data, char *str)
{
	int	squotes;
	int	dquotes;

	squotes = 0;
	dquotes = 0;
	while (*str)
	{
		if (ft_is_quote(*str) && (str + 1) && ft_strchr(str + 1, *str) != NULL)
			str = ft_strchr(str + 1, *str) + 1;
		else
		{
			if (*str == SIMPLE_QUOTES)
				squotes++;
			else if (*str == DOUBLE_QUOTES)
				dquotes++;
			str++;
		}
	}
	if (squotes % 2 != 0 || dquotes % 2 != 0)
	{
		ft_putstr_fd("Missing closing quotes\n", 2);
		free_garbage(data);
		exit(EXIT_FAILURE);
	}
	return (true);
}
