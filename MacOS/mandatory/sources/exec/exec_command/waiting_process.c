/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:25:57 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/15 17:49:58 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** handle_signal_status:
** - This function processes the exit status of a
**		child process after it terminates.
** - Checks if the process was terminated by a signal (e.g., SIGINT or SIGQUIT)
** - Displays appropriate messages for signals
**		and updates the shell's exit status.
** - Ensures that messages for signals are displayed only once using flags.
** - If the process exited normally, updates
**		the exit status for the last forked process.
*/

void	handle_signal_status(int status, t_data *data,
		t_signal_flags *flags, bool last_fork)
{
	g_signal = 0;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT && !(flags->ctrl_c_displayed))
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			data->exit_status = 130;
			flags->ctrl_c_displayed = 1;
		}
		else if (WTERMSIG(status) == SIGQUIT && !(flags->quit_displayed))
		{
			ft_putstr_fd("Quit\n", STDERR_FILENO);
			data->exit_status = 131;
			flags->quit_displayed = 1;
		}
	}
	else if (WIFEXITED(status) && data->error_built == -1 && last_fork == true)
		data->exit_status = WEXITSTATUS(status);
}

/*
** wait_all:
** - This function waits for all child processes
**		created during command execution.
** - Iterates through the list of process IDs (`pids`)
**		and waits for each process to finish.
** - Handles signals like `SIGINT` and `SIGQUIT` during the waiting process.
** - Updates the shell's exit status based on
**		the last process's exit code or signal.
** - Ensures proper cleanup and error handling if `waitpid` fails.
*/

void	wait_all(t_data *data, int nbr_of_fork)
{
	int				i;
	int				status;
	t_signal_flags	flags;

	i = 0;
	flags.ctrl_c_displayed = 0;
	flags.quit_displayed = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i <= nbr_of_fork)
	{
		if (waitpid(data->pids[i], &status, 0) == -1)
		{
			error(data, "WAITPID");
			return ;
		}
		if (i == nbr_of_fork)
			handle_signal_status(status, data, &flags, true);
		else
			handle_signal_status(status, data, &flags, false);
		i++;
	}
}
