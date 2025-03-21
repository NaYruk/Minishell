/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:52:03 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/21 12:09:04 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	Function used to delete an environnement variable.
	Works without the '=' sign in the variable name. 
*/

int	ft_unset(t_data *data)
{
	t_token	*tmp;

	tmp = data->lst_token;
	if (!tmp || !tmp->next)
		return (EXIT_FAILURE);
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->token == ARG)
			ft_delete_env(data, tmp->line);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
