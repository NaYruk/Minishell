/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:17:55 by mcotonea          #+#    #+#             */
/*   Updated: 2025/02/26 15:05:05 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;

	t_data	*data;
	
	if (argc != 1)
	{
		ft_putstr_fd("Error ! nbr of arguments != 1\n", 2);
		exit(EXIT_FAILURE);
	}
	data = init_all();
	while (1)
	{
		data->prompt = readline("SegfaultBros>");
		if (!data->prompt)
			break ; //AJOUTER LA SECURISATION AVEC LE FREE DU DATA PROPREMENT ET EXIT
	}
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	free_garbage(data);
	return (0);
}
