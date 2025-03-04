/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:42:30 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/04 17:00:58 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	malloc_error(t_data *data)
{
	perror("Error with a malloc\n");
	free_garbage(data);
	exit(EXIT_FAILURE);
}
