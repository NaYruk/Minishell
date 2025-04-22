/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:52:03 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/17 01:45:48 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	ft_unset - Removes environment variables.

	This function iterates though the arguments provided to the 'unset' command
	and removes the corrresponding environment variables from the environment.
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
