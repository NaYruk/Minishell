/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:49:08 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/19 07:31:37 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 	i = -1;
		while (data->exec->arg_cmd[++i])
			printf("Arguments de la commande : %s\n", data->exec->arg_cmd[i]);
		printf("Path de l'executable de la commande : %s\n", data->exec->cmd_path);
		printf("Infile de la commande : %s\n", data->exec->infile);
		printf("OUTFILE de la commande : %s\n", data->exec->outfile); */
		
#include "../../includes/minishell.h"

int	get_nbr_redir(t_data *data, t_token *current)
{
	int	nbr_infile;
	int	nbr_outfile;
	int	nbr_append;
	
	nbr_append = 0;
	nbr_infile = 0;
	nbr_outfile = 0;
	while (current != NULL)
	{
		if (current->token == PIPE)
			break ;
		if (current->token == INFILE && current->next->token == ARG)
			nbr_infile++;
		if (current->token == APPEND && (current->next->token) == ARG)
			nbr_append++;
		if (current->token == OUTFILE && (current->next->token == ARG))
			nbr_outfile++;
		current = current->next;
	}
	data->exec->infile = malloc(sizeof(char *) * (nbr_infile + 1));
	if (!data->exec->infile)
		return (-1);
	data->exec->outfile = malloc(sizeof(char *) * (nbr_outfile + 1));
	if (!data->exec->outfile)
		return (-1);
	data->exec->append = malloc(sizeof(char *) * (nbr_append + 1));
	if (!data->exec->append)
		return (-1);
	return (0);
}

int	set_exec_struct(t_data *data, t_token **current)
{
	int	i;
	int	j;
	int k;
	
	j = 0;
	i = 0;
	k = 0;
	if (get_nbr_redir(data, *current) == -1)
		return (-1);
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
			data->exec->infile[i++] = (*current)->next->line;
		if ((*current)->token == APPEND && ((*current)->next->token) == ARG)
			data->exec->append[j++] = (*current)->next->line;
		if ((*current)->token == OUTFILE && ((*current)->next->token) == ARG)
			data->exec->outfile[k++] = (*current)->next->line;
		*current = (*current)->next;
	}
	data->exec->infile[i] = NULL;
	data->exec->outfile[k] = NULL;
	data->exec->append[j] = NULL;
	return (0);
}

void	wait_all(t_data *data, pid_t *pids, int	nbr_of_fork)
{
	int	status;
	
	status = 0;
	while (nbr_of_fork >= 0)
	{
		if (waitpid(pids[nbr_of_fork], NULL, 0) == -1)
		{
			perror("WAITPID");
			error(data);
			return ;
		}
		nbr_of_fork--;
	}
}

int	exec_build(char *line)
{
	if (ft_strcmp(line, "pwd") == 0)
		return (1);
	else if (ft_strcmp(line, "cd") == 0)
		return (1);
	else if (ft_strcmp(line, "exit") == 0)
		return (1);
	else if (ft_strcmp(line, "env") == 0)
		return (1);
	else if (ft_strcmp(line, "echo") == 0)
		return (1);
	else if (ft_strcmp(line, "unset") == 0)
		return (1);
	else if (ft_strcmp(line, "export") == 0)
		return (1);
	return (0);
}

void	exec(t_data *data, t_token *current, pid_t *pids, int (*pipes)[2])
{
	int	cmd_process;
	int	nbr_of_fork;
	int	stdout_backup;
	int	stdin_backup;

	cmd_process = 0;
	nbr_of_fork = -1;
	set_pipes(data, pipes);
	stdout_backup = dup(STDOUT_FILENO);
	stdin_backup = dup(STDIN_FILENO);
	while (current != NULL)
	{
		if (set_exec_struct(data, &current) == -1)
		{
			free_exec_struct(data);
			return ;
		}
		if (exec_build(data->exec->arg_cmd[0]) == 1)
		{
			if (setup_redirection(data, cmd_process, pipes) != -1)
				exec_builtin(data);
			dup2(stdout_backup, STDOUT_FILENO);
		}
		else
		{
			pids[++nbr_of_fork] = fork();
			if (pids[nbr_of_fork] == 0)
				child_process(data, cmd_process, pipes);
		}
		cmd_process++;
		free_exec_struct(data);
	}
	close_pipes(data, pipes);
	wait_all(data, pids, nbr_of_fork);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdout_backup);
	close(stdin_backup);
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
