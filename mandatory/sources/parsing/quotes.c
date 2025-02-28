/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:14:20 by mcotonea          #+#    #+#             */
/*   Updated: 2025/02/28 12:23:18 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}



/* Checker si str[i] == SQ ou DQ et si str[i + 1] == str[i] alors on peut skip 

ft_strchr return l'endroit ou le caractere cible est trouve, si le caractere cible n'est pas trouve alors elle return NULL
*/

int	check_quotes(char *str)
{
	int	squotes;
	int	dquotes;
	
	squotes = 0;
	dquotes = 0;
	while (*str)
	{
		if (ft_is_quote(*str) && (str + 1) && ft_strchr(str + 1 , *str) != NULL)
			str = ft_strchr(str + 1, *str) + 1;
		else
		{
			if (*str == '\'')
				squotes++;
			else if (*str == '"')
				dquotes++;
			str++;
		}
	}
	if (squotes % 2 != 0 || dquotes % 2 != 0)
		return (false);
	return (true);
}