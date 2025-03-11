/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:49:08 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/11 18:37:13 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 	i = -1;
		while (data->exec->arg_cmd[++i])
			printf("Arguments de la commande : %s\n", data->exec->arg_cmd[i]);
		printf("Path de l'executable de la commande : %s\n", data->exec->cmd_path);
		printf("Infile de la commande : %s\n", data->exec->infile);
		printf("OUTFILE de la commande : %s\n", data->exec->outfile); */
		
#include "../../includes/minishell.h"

void	set_exec_struct(t_data *data, t_token **current)
{
	while (*current != NULL)
	{
		if ((*current)->token == PIPE)
		{
			*current = (*current)->next;
			break ;
		}
		if ((*current)->token == CMD)
		{
			get_args_cmd(data, current);
			get_cmd_path(data, current);
		}
		if ((*current)->token == INFILE && ((*current)->next->token) == ARG)
			data->exec->infile = (*current)->next->line;
		if ((*current)->token == APPEND && ((*current)->next->token) == ARG)
			data->exec->infile = (*current)->next->line;
		if ((*current)->token == OUTFILE && ((*current)->next->token) == ARG)
			data->exec->outfile = (*current)->next->line;
		*current = (*current)->next;
	}
}

void	wait_all(t_data *data, pid_t *pids)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < data->nbr_of_command)
	{
		if (waitpid(pids[i], NULL, 0) == -1)
		{
			perror("WAITPID");
			error(data);
		}
	}
}

void	exec(t_data *data, t_token *current, pid_t *pids, int (*pipes)[2])
{
	int	cmd_process;

	cmd_process = 0;
	set_pipes(data, pipes);
	while (current != NULL)
	{
		if (exec_builtin(data) == 1)
		{
			while (current != NULL && current->token != PIPE)
			{
				if (current->token == PIPE)
				{
					current = current->next;
					break ;
				}
				current = current->next;
			}
		}
		set_exec_struct(data, &current);
		pids[cmd_process] = fork();
		if (pids[cmd_process] == 0)
			child_process(data, cmd_process, pipes);
		else
		{
			cmd_process++;
			free_exec_struct(data);
		}
	}
	wait_all(data, pids);
	close_pipes(data, pipes);
}

void	execution(t_data *data)
{
	t_token *current;
	pid_t	*pids;
	int		(*pipes)[2];
	
	current = data->lst_token;
	set_nbr_of_commands(data);
	if (data->nbr_of_command == 0)
		return ;
	init_exec(data);
	get_pids_and_pipes(data, &pids, &pipes);
	exec(data, current, pids, pipes);
	free(pipes);
	free(pids);
	free(data->exec);
}
