/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:32:33 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/07 14:38:04 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	This function executes the builtin commands when
	they are on the command line.
*/

void	exec_builtin(t_data *data)
{
	if (ft_strcmp(data->lst_token->line, "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(data->lst_token->line, "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->lst_token->line, "env") == 0)
		ft_env(data);
	else if (ft_strcmp(data->lst_token->line, "exit") == 0)
		ft_exit(data);
	else if (ft_strcmp(data->lst_token->line, "echo") == 0)
		ft_echo(data);
	return ;
}
