/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:48:21 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/07 08:37:30 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	The function ft_get_home obtains the user's home path.
	The function ft_cd is used to change the current directory. 
	The ~ option takes you directly to home.
*/

static char *ft_get_home(void)
{
	char	*home;

	home = getenv("HOME");
	return (home);
}

int	ft_cd(t_data *data)
{
	char	*home;
	char	*path;
	t_token	*tmp;

	path = NULL;
	tmp = data->lst_token;
	if (!tmp || !tmp->next || ft_strcmp(tmp->next->line, "~") == 0)
	{
		home = ft_get_home();
		if (!home)
		{
			perror("cd: HOME not set");
			return (EXIT_FAILURE);
		}
		path = home;
	}
	else 
		path = tmp->next->line;
	if (chdir(path) == -1)
	{	
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
