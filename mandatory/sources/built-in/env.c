/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:56:15 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/17 00:43:09 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	ft_env - Implements the 'env' command. 

	This functions iterates through the environment variables stored in
	'data->env' and prints each variable that contains an '=' character. 
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
