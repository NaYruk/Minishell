/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:23:30 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/21 12:07:02 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function that checks whether the -n option is present in the first
	arguments of the echo command.
	The function returns 1 if the valid option is present.
*/

static int	check_option(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/* 
	Function that prints all arguments of the echo command. 
	If the line of argument = '\0', it is no printed. 
	The variable first_arg is used to determine if a first argument
	has been arleady printed, to avoid to put a 
	" " (space) before the first argument
*/

static	void	print_args(t_token *tmp)
{
	int	first_arg;

	first_arg = 1;
	while (tmp->next && tmp->next->token == ARG)
	{
		if (tmp->next->line && tmp->next->line[0] != '\0')
		{
			if (!first_arg)
				printf(" ");
			printf("%s", tmp->next->line);
			first_arg = 0;
		}
		tmp = tmp->next;
	}
}

/* 
	Function that reproduces the behavior of the echo command in bash.
*/

int	ft_echo(t_data *data)
{
	t_token	*tmp;
	int		new_line;

	tmp = data->lst_token;
	new_line = 1;
	if (!tmp->next)
		return (printf("\n"), data->exit_status = 0, EXIT_SUCCESS);
	while (tmp->next && (tmp->next->token == ARG
			&& check_option(tmp->next->line)))
	{
		new_line = 0;
		tmp = tmp->next;
	}
	print_args(tmp);
	if (new_line)
		printf("\n");
	return (data->exit_status = 0, EXIT_SUCCESS);
}
