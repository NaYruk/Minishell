/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:48:21 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/07 16:42:36 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	The function ft_get_home obtains the user's home path.
	The function ft_cd is used to change the current directory. 
	The ~ option takes you directly to home.
*/

static char	*ft_get_home(t_data *data)
{
	int	i = 0;
	char	*home;

	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "HOME=", 5) == 0)
		{
			home = ft_substr(data->env[i], 5, ft_strlen(data->env[i]) - 5);
			add_g_c_node(data, &data->g_c, (void **)home, false);
			return (home);
		}
		i++;
	}
	return (NULL);
}

/* static char	*ft_get_prev_dir(t_data *data)
{
	int	i = 0;
	char	*prev_dir;

	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "OLDPWD=", 7) == 0)
		{
			prev_dir = ft_substr(data->env[i], 7, ft_strlen(data->env[i]) - 7);
			add_g_c_node(data, &data->g_c, (void **)prev_dir, false);
			return (prev_dir);
		}
		i++;
	}
	return (NULL);
} */


static void ft_update_env(t_data *data, char *name, char *value)
{
	int	i = 0;
	int	len_total = ft_strlen(name) + ft_strlen(value);

	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0)
		{
			free (data->env[i]);
			data->env[i] = NULL;
			data->env[i] = malloc(sizeof(char) * (len_total + 1));
			ft_strlcpy(data->env[i], name, ft_strlen(name) + 1);
			ft_strlcpy(data->env[i] + (ft_strlen(name)), value, ft_strlen(value) + 1);
		}
		i++;
	}
	return ;
}


int	ft_cd(t_data *data)
{
	char	*home;
	char	*path;
	t_token	*tmp;
	char	*old_pwd = getcwd(NULL, 0);
	
	path = NULL;
	tmp = data->lst_token;
	ft_update_env(data, "OLDPWD=", old_pwd);
	free(old_pwd);
	char *current_dir = getcwd(NULL, 0);
	free(current_dir);
	if (!tmp || !tmp->next || ft_strcmp(tmp->next->line, "~") == 0)
	{
		home = ft_get_home(data);
		if (!home)
		{
			perror("cd: HOME not set");
			return (EXIT_FAILURE);
		}
		path = home;
	}
/* 	else if (ft_strcmp(tmp->next->line, "-") == 0)
	{
		path = ft_get_prev_dir(data);
		if (!path)
		{
			perror("cd: OLDPWD not set");
			free(old_pwd);
			return (EXIT_FAILURE);
		}
	} */
	else 
		path = tmp->next->line;
	if (chdir(path) == -1)
	{	
		perror("cd");
		return (EXIT_FAILURE);
	}
	current_dir = getcwd(NULL, 0);
	ft_update_env(data, "PWD=", current_dir);
	free(current_dir);
	return (EXIT_SUCCESS);
}
