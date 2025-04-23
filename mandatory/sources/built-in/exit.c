/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:26:51 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/23 07:35:51 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	print_exit_error - Print an error message. 
	
	If 'status is 1, it prints the message as is.
	If 'status' is 2, it appends ": numeric argument required" to the message. 
*/

static void	print_exit_error(char *message, int status)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: ", 2);
	if (status == 1)
		ft_putstr_fd(message, 2);
	else
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd(": numeric argument required", 2);
	}
	ft_putstr_fd("\n", 2);
}

/* 
	clean_and_exit - Frees allocated ressources and exit the program. 
*/

static void	clean_and_exit(t_data *data, int status)
{
	free_all(data);
	exit (status);
}

/* 
	number_too_large - Checks if a numeric strings exceeds the range 
					   				of a long long
*/

static int	number_too_large(char *line)
{
	int	size;
	int	i;

	size = ft_strlen(line);
	i = 0;
	if (line[i] == '+' || line[i] == '-')
		i++;
	while (line[i++] == '0')
		size--;
	if (size > 20)
		return (1);
	else if (size == 20)
	{
		if (ft_strcmp(line, "-9223372036854775808") > 0
			&& ft_strcmp(line, "+9223372036854775807") > 0)
			return (1);
	}
	else if (size == 19)
	{
		if (ft_strcmp(line, "9223372036854775807") > 0)
			return (1);
	}
	return (0);
}

/* 
	exit_value - Converts a string to and exit status value. 

	This function converts the string to a long long number and determines
	the appropriate exit status value. If the number is too large, it sets
	'*too_large' to 1 and returns -1. Otherwise, it returns value modulo 256.  
*/

static int	exit_value(char *line, int *too_large)
{
	long long	value;

	if (number_too_large(line))
	{
		print_exit_error(line, 2);
		*too_large = 1;
		return (2);
	}
	value = ft_atoll(line);
	if (value >= 0 && value <= 255)
		return ((int)value);
	return ((int)value % 256);
}

/* 
	ft_exit - Implements the 'exit' command. 

	This function handles the logic for the 'exit' command: 
	- If no arguments, it exits with the last exit status. 
	- If multiple arguments, it prints an error and does not exit. 
	- If the argument is not a valid number, it prints an error and
					exit with status 2.
	- If the argument is valid, it calculates the exit status and exits.
*/

int	ft_exit(t_data *data, char **args_cmd)
{
	int	status;
	int	too_large;

	status = 0;
	too_large = 0;
	if (!args_cmd[1])
	{
		status = data->exit_status;
		ft_putstr_fd("exit\n", 2);
	}
	else if (ft_str_is_digit(args_cmd[1]) != 0 || args_cmd[1][0] == '\0'
				|| number_too_large(args_cmd[1]))
		status = (print_exit_error(args_cmd[1], 2), 2);
	else if (args_cmd[2])
		return (print_exit_error("too many arguments", 1), 1);
	else
	{
		status = exit_value(args_cmd[1], &too_large);
		if (!too_large)
			ft_putstr_fd("exit\n", 2);
	}
	return (clean_and_exit(data, status), status);
}
