/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:17:55 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/17 17:09:07 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal = 0;

void	update_exit_status(t_data *data)
{
	if (g_signal)
	{
		data->exit_status = g_signal + 128;
		g_signal = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data = NULL;
	int		status;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error ! nbr of arguments != 1\n", 2);
		exit(EXIT_FAILURE);
	}
	data = init_all(envp);
	while (1)
	{
		setup_signals_interactive();
		data->prompt = readline("SegfaultBros> ");
		if (!data->prompt)
			break ;
		if (g_signal == SIGINT)
			update_exit_status(data);
		if (data->prompt[0] != '\0')
		{
			add_history(data->prompt);
			if (tokenization(data) == 0)
				execution(data);
		}
		free(data->prompt);
		free_token(data);
	}
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	status = data->exit_status;
	return (free_garbage(data), status);
}
