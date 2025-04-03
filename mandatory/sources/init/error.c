/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:12:55 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/03 18:14:31 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	malloc_error(t_data *data)
{
	perror("Error with a malloc\n");
	if (data->exec)
		free_exec_struct(data);
	free_garbage(data);
	exit(EXIT_FAILURE);
}

void	error(t_data *data)
{
	if (data->exec)
		free_exec_struct(data);
	free_garbage(data);
	exit(EXIT_FAILURE);
}

void	ft_error_name(char *str)
{
	ft_putstr_fd("'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}
