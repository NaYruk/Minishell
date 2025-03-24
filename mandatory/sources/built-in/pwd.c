/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:41:06 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/24 00:24:56 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	The ft_pwd function is used to obtain the
	process's current working directory.
*/

int	ft_pwd(t_data *data)
{
	char	*dir;

	(void)data;
	dir = getcwd(NULL, 0);
	if (!dir)
	{
		perror("pwd");
		return (data->exit_status = 1, EXIT_FAILURE);
	}
	printf("%s\n", dir);
	free(dir);
	return (data->exit_status = 0, EXIT_SUCCESS);
}
