/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:42:30 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/07 12:01:30 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	malloc_error(t_data *data)
{
	perror("Error with a malloc\n");
	if (data->exec != NULL)
		free_exec_struct(data);
	free_garbage(data);
	exit(EXIT_FAILURE);
}
