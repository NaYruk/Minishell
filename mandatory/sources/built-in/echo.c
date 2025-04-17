/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:23:30 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/17 00:41:32 by melvin           ###   ########.fr       */
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
	print_args - Prints the arguments of the 'echo' command. 

	It prints each argument, separated by a space, unless the argument
	is an empty line. 
*/

static	void	print_args(char **cmd_args, int *index)
{
	while (cmd_args[*index + 1])
	{
		if (cmd_args[*index + 1])
		{
			if (cmd_args[*index + 1][0] != '\0')
				printf("%s", cmd_args[*index + 1]);
			if (cmd_args[*index + 2])
				printf(" ");
		}
		(*index)++;
	}
}

/* 
	ft_echo - Implements the 'echo' command:
	
	- If no arguments, it prints a newline and exits successfully. 
	- It checks for the '-n' option.
	- Prints args, separated by spaces. 
*/

int	ft_echo(t_data *data, char **args_cmd)
{
	int		i;
	int		new_line;

	new_line = 1;
	i = 0;
	if (!args_cmd[i + 1])
		return (printf("\n"), data->exit_status = 0, EXIT_SUCCESS);
	while (args_cmd[i + 1] && check_option(args_cmd[i + 1]))
	{
		new_line = 0;
		i++;
	}
	print_args(args_cmd, &i);
	if (new_line)
		printf("\n");
	return (data->exit_status = 0, EXIT_SUCCESS);
}
