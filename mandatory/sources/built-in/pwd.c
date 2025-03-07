/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:41:06 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/07 08:31:47 by mcotonea         ###   ########.fr       */
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
		return (1);
	printf("%s\n", dir);
	free(dir);
	return (0);
}
