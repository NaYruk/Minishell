/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:52:03 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/29 02:30:32 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function used to delete an environnement variable.
	Works without the '=' sign in the variable name. 
*/

int	ft_unset(t_data *data, char **args_cmd)
{
	int	i;

	i = 0;
	if (!args_cmd[0] || !args_cmd[i + 1])
		return (data->exit_status = 0, EXIT_SUCCESS);
	i++;
	while (args_cmd[i])
	{
		ft_delete_env(data, args_cmd[i]);
		i++;
	}
	return (data->exit_status = 0, EXIT_SUCCESS);
}
