/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:26:51 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/21 12:05:10 by mcotonea         ###   ########.fr       */
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

static int	ft_str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

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
	free_garbage(data);
	free_token(data);
	exit (status);
}

static int	exit_value(char *line)
{
	long long	value;

	value = ft_atoll(line);
	if (value >= 0 && value <= 255)
		return ((int)value);
	return ((int)value % 256);
}

int	ft_exit(t_data *data)
{
	t_token		*tmp;
	int			status;

	status = 0;
	tmp = data->lst_token;
	if (!tmp->next)
		status = 0;
	else if (tmp->next && tmp->next->next)
	{
		print_exit_error("too many arguments", 1);
		status = 1;
		return (status);
	}
	else if (tmp->next && ft_str_is_digit(tmp->next->line) == 1)
	{
		print_exit_error(tmp->next->line, 2);
		status = 2;
		exit(status);
	}
	else if (tmp->next)
		status = exit_value(tmp->next->line);
	clean_and_exit(data, status);
	return (status);
}
