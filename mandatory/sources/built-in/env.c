/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:56:15 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/24 00:24:13 by melvin           ###   ########.fr       */
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
	if (!data || !data->env || data->lst_token->next)
	{
		return (data->exit_status = 1, EXIT_FAILURE);
	}
	while (data->env[i])
	{
		ft_printf("%s\n", data->env[i]);
		i++;
	}
	return (data->exit_status = 0, EXIT_SUCCESS);
}
