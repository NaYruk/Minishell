/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:48:21 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/05 15:38:16 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	The exis status of the cd command is0 when it succeeds and 1 when it fails
*/

static char *ft_get_home(void)
{
	char	*home;

	home = getenv("HOME");
	return (home);
}

static char	*ft_get_dir(void)
{
	char	*line;
	
	line = getcwd(NULL, 0);
	return (line);
	
}

/* 
	cd ~ ou cd (vide) renvoie vers le home du user
	cd - renvoie vers le repertoire precedent
	
*/

int	ft_cd(t_data *data)
{
	char	*home;
	char	*current_dir;
	char	*path = NULL;
	t_token	*tmp;

	current_dir = ft_get_dir();
	if (!current_dir)
		return (1);
	ft_strlcpy(data->prev_folder, current_dir, ft_strlen(current_dir) + 1);
	free (current_dir);
	tmp = data->lst_token;
	if (!tmp || !tmp->next|| ft_strcmp(tmp->next->line, "~") == 0)
	{
		home = ft_get_home();
		if (!home)
			return (1);
		path = home;
	}
	else if (ft_strcmp(tmp->next->line, "-") == 0)
	{
		if (ft_strlen(data->prev_folder) > 0)
			path = data->prev_folder;
		else
			return (1);
	}
	else 
		path = tmp->next->line;
	if (chdir(path) == -1)
	{	
		return (1);
	}
	return (0);
}
