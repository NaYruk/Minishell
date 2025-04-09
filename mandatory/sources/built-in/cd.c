/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:48:21 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/09 12:38:55 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function to display an error message when using cd.
*/

static int	cd_error(char *path, int many_args)
{
	if (many_args)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
	}
	return (EXIT_FAILURE);
}

/* 
	Function to obtain the path to use chdir. 
	If no argument or cd ~, the path obtained is the home path. 
	If cd -, the path obtained is the path to the previous directory. 
	Otherwise, the path is the argument to the cd command. 
*/

static char	*get_cd_path(t_data *data, char **args_cmd)
{
	char	*home;
	char	*path;

	if (!args_cmd[1])
	{
		home = ft_getenv(data, "HOME", NULL);
		if (!home)
		{
			perror("cd: HOME not set");
			return (NULL);
		}
		path = home;
	}
	else if (ft_strcmp(args_cmd[1], "-") == 0)
	{
		path = ft_getenv(data, "OLDPWD", NULL);
		if (!path)
		{
			perror("cd: OLDPWD not set");
			return (NULL);
		}
	}
	else
		path = args_cmd[1];
	return (path);
}

int	ft_cd(t_data *data, char **args_cmd)
{
	char	*current_dir;
	char	*old_pwd;
	char	*path;

	if (args_cmd[0] && args_cmd[1] && args_cmd[2])
		return (data->exit_status = 1, cd_error(NULL, 1));
	old_pwd = getcwd(NULL, 0);
	path = get_cd_path(data, args_cmd);
	if (!path)
		return (free (old_pwd), data->exit_status = 1, EXIT_FAILURE);
	if (chdir(path) == -1 && args_cmd[1][0] != '\0')
		return (free(old_pwd), data->exit_status = 1, cd_error(path, 0));
	ft_update_env(data, "OLDPWD", old_pwd);
	free (old_pwd);
	current_dir = getcwd(NULL, 0);
	ft_update_env(data, "PWD", current_dir);
	free (current_dir);
	return (data->exit_status = 0, EXIT_SUCCESS);
}
