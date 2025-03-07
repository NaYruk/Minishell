/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:23:30 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/07 15:26:05 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/* echo sans rien renvoie 0 et un \n */

int	check_option(char *str)
{
	int	i;
	int	len;
	
	i = 0;
	len = ft_strlen(str);
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

int	ft_echo(t_data *data)
{
	t_token *tmp;

	tmp = data->lst_token;
	if (!tmp->next)
		return (printf("\n"), EXIT_SUCCESS);
	if (tmp->next->token == ARG && check_option(tmp->next->line) == 1)
	{
		tmp = tmp->next;
		while (tmp->next && tmp->next->token == ARG)
		{
			printf("%s", tmp->next->line);
			tmp = tmp->next;
			if (tmp->next && tmp->next->token == ARG)
				printf(" ");
		}
		return (EXIT_SUCCESS);
	}
	else if (tmp->next->token == ARG)
	{
		while (tmp->next && tmp->next->token == ARG)
		{
			printf("%s", tmp->next->line);
			tmp = tmp->next;
			if (tmp->next && tmp->next->token == ARG)
				printf(" ");
		}
		printf("\n");
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

/* int	ft_echo(t_data *data)
{
	t_token *tmp;

	tmp = data->lst_token;
	if (!tmp->next)
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	else if (tmp->next->token == ARG)
	{
		while (tmp->next && tmp->next->token == ARG)
		{
			printf("%s", tmp->next->line);
			tmp = tmp->next;
			if (tmp->next && tmp->next->token == ARG)
				printf(" ");
		}
		printf("\n");
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);	
} */
