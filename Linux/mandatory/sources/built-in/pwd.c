/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:41:06 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/17 01:44:07 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	ft_pwd - Prints the current working directory. 
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
