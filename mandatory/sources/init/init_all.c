/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:39:36 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/11 00:44:21 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Function for copy the envp in a char ** variable */

void	copy_envp(char **envp, t_data *data)
{
	int	line_number;
	int	i;

	line_number = 0;
	while (envp[line_number] != NULL)
		line_number++;
	data->env = malloc(sizeof(char *) * (line_number + 1));
	if (!data->env)
		malloc_error(data);
	i = -1;
	while (envp[++i] != NULL)
		data->env[i] = ft_strdup(envp[i]);
	data->env[i] = NULL;
}

void	update_shlvl(t_data *data)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = ft_getenv(data, "SHLVL", NULL);
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str);
		if (shlvl < 0)
			shlvl = -1;
	}
	else
		shlvl = 0;
	shlvl++;
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		malloc_error(data);
	ft_update_env(data, "SHLVL", shlvl_str);
	free (shlvl_str);
}

void	minienv(t_data *data)
{
	char	*pwd;

	pwd = NULL;
	data->env = malloc(sizeof(char *) * 5);
	if (!data->env)
		malloc_error(data);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		malloc_error(data);
	data->env[0] = ft_strdup("PWD=");
	data->env[0] = ft_strjoin(data->env[0], pwd);
	data->env[1] = ft_strdup("SHLVL=0");
	data->env[2] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	data->env[3] = ft_strdup("OLDPWD");
	data->env[4] = NULL;
	free (pwd);
	if (!data->env[0] || !data->env[1] || !data->env[2] || !data->env[3])
		malloc_error(data);
}

/* 
	Function for initialize all data need in Minishell 
	Malloc the struct data,
	Call the init_garbage_collector function for init the garbage collector
	All Malloc need to be follow by add_new_g_b_node function for adding
	of the malloc adress in the garbage collector.
*/

t_data	*init_all(char **envp)
{
	t_data	*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("Error with a malloc\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(data, 0, sizeof(t_data));
	data->old_read_pipe = -1;
	data->current_pipe[0] = -1;
	data->current_pipe[1] = -1;
	if (!envp || !envp[0])
		minienv(data);
	else
		copy_envp(envp, data);
	update_shlvl(data);
	return (data);
}
