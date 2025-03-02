/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:08:52 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/28 18:49:45 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/* It is the main Function for the tokenisation !*/

void	tokenization(t_data *data)
{
	cut_the_line(data);
	return ;
}
