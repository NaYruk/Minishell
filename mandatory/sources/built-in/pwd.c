/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:41:06 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/05 15:23:02 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Exit status of pwd is 0
	The getcwd function is used to obtain the process's 
	current working directory.
	You can also obtain the pwd by searching in environment variables.


	char *dir = getcwd(NULL, 0);
	printf("%s\n", dir);
	
*/

/* int	ft_pwd(t_data *data)
{
	int		i;
	char	*pwd;

	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			pwd = ft_strchr(data->env[i], '=');
			if (pwd)
			{
				printf("%s\n", pwd + 1);
				break ;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
} */

int	ft_pwd(t_data *data)
{
	char	*dir;

	(void)data;
	dir = getcwd(NULL, 0);
	if (!dir)
		return (1);
	printf("%s\n", dir);
	return (0);
}
