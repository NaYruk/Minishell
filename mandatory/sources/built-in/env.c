/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:56:15 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/29 02:03:11 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function to display all environnement variables. 
*/

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->env)
	{
		return (data->exit_status = 1, EXIT_FAILURE);
	}
	while (data->env && data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
			printf("%s\n", data->env[i]);
		i++;
	}
	return (data->exit_status = 0, EXIT_SUCCESS);
}
