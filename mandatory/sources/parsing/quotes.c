/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:14:20 by mcotonea          #+#    #+#             */
/*   Updated: 2025/02/28 17:22:14 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_quote(char c)
{
	if (c == SIMPLE_QUOTES || c == DOUBLE_QUOTES)
		return (true);
	return (false);
}

static int	ft_is_white_spaces(char c)
{
	if (c == 32 || (c >= 7 && c <= 13))
		return (1);
	return (0);
}

/* static int	ft_gettype(char *str)
{
	int		i;
	char	*line;

	while (*str)
	{
		if (*str == '|')
			return (PIPE);
		if (*str == '<' || *str == '>')
			return (REDIR);
		if (*str == '<' && *str + 1 == '<')
			return (HEREDOC);
		if (*str == '>' && *str + 1 == '>')
			return (APPEND);
		if (*str == '&' && *str + 1 == '&')
			return (AND);
		if (*str == '|' && *str + 1 == '|')
			return (OR);
	}
	return (0);
} */


void	ft_token(t_data *data)
{
	char	*line;
	int		i = 0;
	int		in_quotes = 0;
	int		count;
	char	quote_char = '\0';

	while (data->prompt[i] != '\0')
	{
		while (ft_is_white_spaces(data->prompt[i]) && data->prompt[i] && !in_quotes)
			i++;
		if (data->prompt[i] == SIMPLE_QUOTES || data->prompt[i] == DOUBLE_QUOTES)
		{
			quote_char = data->prompt[i];
			in_quotes = 1;
			i++;
		}
		count = 0;
		while (data->prompt[i] && (in_quotes || !ft_is_white_spaces(data->prompt[i])))
		{
			if (quote_char == data->prompt[i] && in_quotes)
				in_quotes = 0;
			i++;
			count++;
		}
		line = ft_strndup(&data->prompt[i - count], count);
		if (!line)
		{
			perror("Error with a malloc\n");
			free_garbage(data);
			exit(EXIT_FAILURE);
		}
		add_new_token_node(data, &data->lst_token, line);
	}
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
