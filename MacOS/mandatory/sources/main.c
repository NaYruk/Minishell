/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:17:55 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/18 18:57:01 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../includes/minishell.h"

/* Global Variable for Signal */

int	g_signal = 0;

/*
** update_exit_status:
** - Updates the exit status of the shell based on the received signal.
** - If a signal is received, the exit status is set to `signal + 128`.
** - Resets the global signal variable to 0 after updating.
*/

void	update_exit_status(t_data *data)
{
	if (g_signal)
	{
		data->exit_status = g_signal + 128;
		g_signal = 0;
	}
}

/*
** execute_minishell:
** - Main loop of the Minishell program.
** - Displays the prompt and waits for user input.
** - Handles signals and updates the exit status accordingly.
** - Processes the input through tokenization and executes commands.
** - Frees allocated resources after each command execution.
** - Exits the loop when the user sends EOF (Ctrl+D).
*/

static void	execute_minishell(t_data *data)
{
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
	return ;
}

/*
** main:
** - Entry point of the Minishell program.
** - Validates the number of arguments passed to the program.
** - Initializes the shell environment and data structures.
** - Starts the main execution loop for the shell.
** - Cleans up resources and exits with the appropriate status.
*/

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		status;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error ! nbr of arguments != 1\n", 2);
		exit(EXIT_FAILURE);
	}
	data = NULL;
	data = init_all(envp);
	execute_minishell(data);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	status = data->exit_status;
	return (free_garbage(data), status);
}
