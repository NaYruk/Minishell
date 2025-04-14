/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:26:51 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/14 17:45:26 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function to built-in command exit.
	Exit status of exit is 0.

	10000000000000000000
	exit a : quitte le programme et renvoie 2
	exit: a: numeric argument required
	

	exit 122 33 ou exit 122 a: ne quitte pas et renvoie 1
	exit: too many arguments

	
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

static void	clean_and_exit(t_data *data, int status)
{
	printf("exit\n");
	free_garbage(data);
	exit (status);
}

static int	number_too_large(char *line)
{
	int	size;
	int	i;

	size = ft_strlen(line);
	i = 0;
	while (line[i] == '0')
	{
		i++;
		size--;
	}
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

int	ft_exit(t_data *data, char **args_cmd)
{
	int			status;
	int			too_large;

	status = 0;
	too_large = 0;
	if (!args_cmd[1])
		status = data->exit_status;
	else if (args_cmd[1] && args_cmd[2])
	{
		print_exit_error("too many arguments", 1);
		status = 1;
		return (data->exit_status = status);
	}
	else if (args_cmd[1] && (ft_str_is_digit(args_cmd[1]) == 1 || args_cmd[1][0] == '\0'))
	{
		print_exit_error(args_cmd[1], 2);
		status = 2;
		exit(status);
	}
	else if (args_cmd[1])
		status = exit_value(args_cmd[1], &too_large);
	clean_and_exit(data, status);
	return (status);
}
