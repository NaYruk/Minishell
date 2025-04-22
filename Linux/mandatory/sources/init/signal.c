/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:57:17 by mcotonea          #+#    #+#             */
/*   Updated: 2025/04/17 18:20:50 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
	In interactive mode, CTRL+C (SIGINT) interrupts input and display a new
	prompt. CTRL+\ is ignored.
*/

static void	sig_sigint_interactive(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals_interactive(void)
{
	signal(SIGINT, &sig_sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
}

/* 
	In the case of a heredoc, CTRL+C inetrrupts the heredoc and returns to
	the main prompt. 
	CTRL+\ is ignored. 
*/

static void	sig_sigint_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		ft_putstr_fd("\n", STDOUT_FILENO);
		close(STDIN_FILENO);
	}
}

void	setup_signals_heredoc(void)
{
	signal(SIGINT, &sig_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

/* 
	In the case of a child process, we must restore the default CTRL+C
	and CTRL+\ signals. 
*/

void	setup_signals_execution(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
