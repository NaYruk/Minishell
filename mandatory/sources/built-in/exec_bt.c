/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:32:33 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/12 11:08:54 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	This function executes the builtin commands when
	they are on the command line.
*/

int	exec_builtin(t_data *data)
{
	if (ft_strcmp(data->lst_token->line, "pwd") == 0)
		return (ft_pwd(data), 1);
	else if (ft_strcmp(data->lst_token->line, "cd") == 0)
		return (ft_cd(data), 1);
	else if (ft_strcmp(data->lst_token->line, "exit") == 0)
		return (ft_exit(data), 1);
	else if (ft_strcmp(data->lst_token->line, "env") == 0)
		return (ft_env(data), 1);
	else if (ft_strcmp(data->lst_token->line, "echo") == 0)
		return (ft_echo(data), 1);
	else if (ft_strcmp(data->lst_token->line, "unset") == 0)
		return (ft_unset(data), 1);
	return (0);
}
