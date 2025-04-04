/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:25:57 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/04 15:53:19 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_signal_status(int status, t_data *data, int *quit_displayed)
{
    if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == SIGINT)
        {
            ft_putstr_fd("\n", STDOUT_FILENO);
            data->exit_status = 130;
        }
        else if (WTERMSIG(status) == SIGQUIT && !(*quit_displayed))
        {
            ft_putstr_fd("Quit\n", STDERR_FILENO);
            data->exit_status = 131;
            *quit_displayed = 1;
        }
    }
    else if (WIFEXITED(status) && data->error_built == -1)
        data->exit_status = WEXITSTATUS(status);
}

void	wait_all(t_data *data, int nbr_of_fork)
{
	int	i;
	int	status;
	int	quit_displayed;

	i = 0;
	quit_displayed = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i <= nbr_of_fork)
	{
		if (waitpid(data->pids[i], &status, 0) == -1)
		{
			perror("WAITPID");
			error(data);
			return ;
		}
		handle_signal_status(status, data, &quit_displayed);
		i++;
	}
}
