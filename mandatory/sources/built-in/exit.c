/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:26:51 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/07 08:08:25 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function to built-in command exit.
	Exit status of exit is 0.
*/

int	ft_exit(t_data *data)
{
	free_garbage(data);
	free_token(data);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}
