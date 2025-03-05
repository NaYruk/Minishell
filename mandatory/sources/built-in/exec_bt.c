/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:32:33 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/05 15:42:38 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(t_data *data)
{
	if (ft_strcmp(data->lst_token->line, "pwd") == 0)
		ft_pwd(data);
	if (ft_strcmp(data->lst_token->line, "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->lst_token->line, "exit") == 0)
		ft_exit(data);
	return ;
}