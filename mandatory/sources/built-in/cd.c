/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:48:21 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/23 07:50:40 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	cd_error - Displays an error message for the 'cd' command.
	If 'many_args' is true, it print an error message for too many arguments. 
	Otherwise, it prints an error message for the specified path. 
*/

static int	cd_error(t_data *data, char *path, int many_args)
{
	if (many_args)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		data->exit_status = 1;
		return (EXIT_FAILURE);
	}
	else if (path[0] != '\0')
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
	}
	if (path && path[0] != '\0')
	{
		data->exit_status = 1;
		return (EXIT_FAILURE);
	}
	else
	{
		data->exit_status = 0;
		return (0);
	}
}

/* 
	get_cd_path - Determines the path to use for the 'cd' command.
	This function determunes the target path for the 'cd' command,
	based on the arguments:
	- If no arguments, it retrieves the 'HOME'.
	- If the argument is "-", it retrieves the 'OLDPWD'. 
	- Otherwise, it uses the provided argument as the path.
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
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
		path = home;
	}
	else if (ft_strcmp(args_cmd[1], "-") == 0)
	{
		path = ft_getenv(data, "OLDPWD", NULL);
		if (!path)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			return (NULL);
		}
	}
	else
		path = args_cmd[1];
	return (path);
}

/* 
	ft_cd - Implements the 'cd' command. 

	This functions handles the logic for changing 
	the current working directory:
	- If too many arguments, it displays an error. 
	- Retrieves the current directory and determine 
	  the target path with get_cd_path. 
	- Change the directory using 'chdir'. 
	- Updates the 'OLDPWD' et 'PWD'. 
*/

int	ft_cd(t_data *data, char **args_cmd)
{
	char	*current_dir;
	char	*old_pwd;
	char	*path;
	int		available;

	if (args_cmd[0] && args_cmd[1] && args_cmd[2])
		return (cd_error(data, NULL, 1));
	old_pwd = getcwd(NULL, 0);
	path = get_cd_path(data, args_cmd);
	if (!path)
		return (free (old_pwd), data->exit_status = 1, 1);
	if (chdir(path) == -1)
		return (free(old_pwd), cd_error(data, path, 0));
	ft_getenv(data, "OLDPWD", &available);
	if (available == 0)
		ft_add_new_env(data, "OLDPWD", old_pwd);
	else
		ft_update_env(data, "OLDPWD", old_pwd);
	current_dir = getcwd(NULL, 0);
	ft_getenv(data, "PWD", &available);
	if (available == 0)
		ft_add_new_env(data,"PWD", current_dir);
	else
		ft_update_env(data, "PWD", current_dir);
	return (free (old_pwd), free(current_dir), data->exit_status = 0, 0);
}
