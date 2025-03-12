/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:23:30 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/12 10:25:40 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_option(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
	
}

static int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static char	*expand_var(t_data *data, char *str)
{
	int		len_var;
	char	*var;
	char	*value;
	char	*result;

	len_var = 0;
	var = ft_strchr(str, '$');
	if (!var)
		return (NULL);
	var = var + 1;
	while (var[len_var] && (ft_isalnum(var[len_var]) || var[len_var] == '_'))
		len_var++;
	value = ft_strndup(var, len_var);
	if (!value)
		return (NULL);
	result = ft_getenv(data, value);
	if (!result)
		return (free(value), NULL);
	return (free(value), result);
}

int	ft_echo(t_data *data)
{
	t_token *tmp;
	char	*expand;
	int		newline;

	tmp = data->lst_token;
	expand = NULL;
	newline = 1;
	if (!tmp->next)
	return (printf("\n"), EXIT_SUCCESS);
	while (tmp->next->token == ARG && check_option(tmp->next->line))
	{
		newline = 0;
		tmp = tmp->next;
	}
	while (tmp->next && tmp->next->token == ARG)
	{
		if (check_dollar(tmp->next->line))
		{
			expand = expand_var(data, tmp->next->line);
			if (expand)
				printf("%s", expand);
		}
		else
			printf("%s", tmp->next->line);
		tmp = tmp->next;
		if (tmp->next && tmp->next->token == ARG)
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (EXIT_SUCCESS);
}

