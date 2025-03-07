/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:56:15 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/07 09:21:49 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_data	*data)
{
	int i;
	
	i = 0;
	if (!data || !data->env)
	{
		return (1);
	}
	while (data->env[i])
	{
		ft_printf("%s\n", data->env[i]);
		i++;
	}
	return (0);	
}
