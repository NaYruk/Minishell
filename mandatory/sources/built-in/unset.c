/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:52:03 by mcotonea          #+#    #+#             */
/*   Updated: 2025/03/12 11:14:30 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
