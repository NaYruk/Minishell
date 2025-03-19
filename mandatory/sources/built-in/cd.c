/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:48:21 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/19 07:54:39 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function to display an error message when using cd.
*/

static int	cd_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	return (EXIT_FAILURE);
}

/* 
	Function to obtain the path to use chdir. 
	If no argument or cd ~, the path obtained is the home path. 
	If cd -, the path obtained is the path to the previous directory. 
	Otherwise, the path is the argument to the cd command. 
*/

static char	*get_cd_path(t_data *data, t_token *tmp)
{
	char	*home;
	char	*path;

	if (!tmp || !tmp->next || ft_strcmp(tmp->next->line, "~") == 0)
	{
		home = ft_getenv(data, "HOME");
		if (!home)
		{
			perror("cd: HOME not set");
			return (NULL);
		}
		path = home;
	}
	else if (ft_strcmp(tmp->next->line, "-") == 0)
	{
		path = ft_getenv(data, "OLDPWD");
		if (!path)
		{
			perror("cd: OLDPWD not set");
			return (NULL);
		}
	}
	else
		path = tmp->next->line;
	return (path);
}

int	ft_cd(t_data *data)
{
	char	*current_dir;
	char	*old_pwd;
	char	*path;
	t_token	*tmp;

	tmp = data->lst_token;
	old_pwd = getcwd(NULL, 0);
	path = get_cd_path(data, tmp);
	if (!path)
		return (EXIT_FAILURE);
	if (chdir(path) == -1)
		return (cd_error(path));
	ft_update_env(data, "OLDPWD", old_pwd);
	free (old_pwd);
	current_dir = getcwd(NULL, 0);
	ft_update_env(data, "PWD", current_dir);
	free (current_dir);
	return (EXIT_SUCCESS);
}
