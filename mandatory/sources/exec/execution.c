/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:49:08 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/11 03:54:47 by mmilliot         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

/*int	setup_redirection(t_data *data, int i, int (*pipes)[2])
{
	//...
}

void	child_process(t_data *data, int i, int (*pipes)[2])
{
	if (setup_redirection(data, i, pipes) == -1)
		return ;
}*/

void	exec(t_data *data, t_token *current, pid_t *pids, int (*pipes)[2])
{
	(void)pids;
	(void)pipes;
	while (current != NULL)
	{
		set_exec_struct(data, &current);
		/*int	i = -1;
		while (data->exec->arg_cmd[++i])
			printf("Arguments de la commande : %s\n", data->exec->arg_cmd[i]);
		printf("Path de l'executable de la commande : %s\n", data->exec->cmd_path);
		printf("Infile de la commande : %s\n", data->exec->infile);
		printf("OUTFILE de la commande : %s\n", data->exec->outfile);*/ 
		free_exec_struct(data);
	}
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
