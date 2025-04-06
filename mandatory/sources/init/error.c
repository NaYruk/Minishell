/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:12:55 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/06 23:41:01 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

void	ft_free_env(char **tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		free (tmp[i]);
		i++;
	}
	free (tmp);
	return ;
}
