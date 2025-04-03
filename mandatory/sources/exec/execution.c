/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:49:08 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/03 17:19:57 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* WAIT_ALL = After the execution, we wait all child process. */

void	wait_all(t_data *data, int nbr_of_fork)
{
	int	i;
	int	status;
	int	quit_displayed;

	if (data->is_builtin_cmd)
	{
		if (data->is_builtin_cmd[data->nbr_of_command - 1] == true)
			return ;
	}
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
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
			{
				ft_putstr_fd("\n", STDOUT_FILENO);
				data->exit_status = 130;
			}
			else if (WTERMSIG(status) == SIGQUIT && !quit_displayed)
			{
				ft_putstr_fd("Quit\n", STDERR_FILENO);
				data->exit_status = 131;
				quit_displayed = 1;
			}
		}
		if (WIFEXITED(status) && data->error_built == -1)
			data->exit_status = WEXITSTATUS(status);
		i++;
	}
}

/* Function for detected if a builtin is present */

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

int	need_to_exec_builtin(t_data *data, int *cmd_process, int *nbr_of_fork)
{
	if (data->nbr_of_command > 1)
	{
		data->pids[++(*nbr_of_fork)] = fork();
		if (data->pids[*nbr_of_fork] == 0)
		{
			if (exec_builtin(data, data->exec->arg_cmd, *cmd_process) == -1)
			{
				data->error_built = 1;
				exit(EXIT_FAILURE);
			}
			exit(data->exit_status);
		}
		else
		{
			if (*cmd_process > 0)
				close(data->old_pipe[0]);
			if (*cmd_process < data->nbr_of_command - 1)
				close(data->current_pipe[1]);
		}
	}
	else
	{
		data->is_builtin_cmd[*cmd_process] = true;
		if (exec_builtin(data, data->exec->arg_cmd, *cmd_process) == -1)
		{
			data->error_built = 1;
			return (-1);
		}
		dup2(data->stdin_backup, STDIN_FILENO);
		dup2(data->stdout_backup, STDOUT_FILENO);
		close(data->current_pipe[0]);
		close(data->current_pipe[1]);
	}
	return (0);
}

/*
	EXEC_BUILD_OR_CMD = Function for exec a builtin if the token is a builtin
						exec other cmd if the token is not a builtin.
	In the case of a Heredoc, exec_heredoc before the rest of execution.
	In the case of a builtin, setup the redirections, and exec the builtin.
	In the case of an other command, create a child process, setup the
	redirections in the child, and exec the command with execve.
*/

void	exec_build_or_cmd(t_data *data, int *cmd_process, int *nbr_of_fork)
{
	if (exec_build(data->exec->arg_cmd[0]))
	{
		if (need_to_exec_builtin(data, cmd_process, nbr_of_fork) == -1)
			return ;
	}
	else
	{
		data->pids[++(*nbr_of_fork)] = fork();
		if (data->pids[*nbr_of_fork] == 0)
			child_process(data, *cmd_process);
		else
		{
			if (*cmd_process > 0)
				close(data->old_pipe[0]);
			if (*cmd_process < data->nbr_of_command - 1)
				close(data->current_pipe[1]);
		}
	}
}

bool	get_next_pipe_or_null(t_token **current)
{
	while (*current && (*current)->token != PIPE)
		*current = (*current)->next;
	if (*current && (*current)->token == PIPE)
		return (true);
	return (false);
}

/*
	EXEC = Function for the final execution :
		Set all redirection, exec builtin if the token contain a builtin,
		else exec a child process and use execve for execute the command.
		
	SET_EXEC_STRUCT = Function for set the exec structure. 
		set a char ** infile, outfile and append in the case
		of < infile1 < infile2 < infile3 etc... same for outfile and append.
		set a char **arg_cmd and a char *cmd_path for execve function.
		SET_EXEC_STRUCT is a setup for the final execution.
		IN : 	./set_exec_struct.c
				./get_args.c
				./get_cmd_path.c
		
	EXEC_BUILD_OR_CMD = Function for exec a builtin if the token is a builtin
						exec other cmd if the token is not a builtin.
						
	WAIT_ALL = After the execution of each command, we wait all child process.
	we have a backup of STDIN and STDOUT because in the case of a builtin,
	and redirect, we dup2 the STDIN or STDOUT in the parent process.
	We need to restore at origin STDIN and STDOUT in the parent after the
	redirection.
*/	

void	allocate_status_command(t_data *data)
{
	if (data->nbr_of_command > 0)
	{
		data->is_builtin_cmd = ft_calloc(data->nbr_of_command, sizeof(bool));
		if (!data->is_builtin_cmd)
			malloc_error(data);
		add_g_c_node(data, &data->g_c, (void **)data->is_builtin_cmd, false);
	}
}

void	exec(t_data *data, t_token *current)
{
	int	cmd_process;
	int	nbr_of_fork;

	cmd_process = 0;
	nbr_of_fork = -1;
	allocate_status_command(data);
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);
	while (current != NULL)
	{
		if (cmd_process < data->nbr_of_command - 1)
		{
			if (pipe(data->current_pipe) == -1)
				malloc_error(data);
		}
		if (set_exec_struct(data, &current) == -1)
		{
			if (get_next_pipe_or_null(&current) == false)
			{
				free_exec_struct(data);
				break ;
			}
			else if (cmd_process < data->nbr_of_command - 1)
				close(data->current_pipe[1]);
		}
		else
		{
			if (data->nbr_of_command > 0 && data->exec->arg_cmd)	
				exec_build_or_cmd(data, &cmd_process, &nbr_of_fork);
		}
		data->old_pipe[0] = data->current_pipe[0];
		data->old_pipe[1] = data->current_pipe[1];
		cmd_process++;
		free_exec_struct(data);
	}
	wait_all(data, nbr_of_fork);
	close (data->stdin_backup);
	close (data->stdout_backup);
}

/*
	Main Function for the execution :
	set_nbr_of_commands = Function for check the nbr of command in token.
	init_exec = Function for initialize the exec Struct
	EXEC STRUCT :
	typedef struct s_exec
	{
		char			**infile;
		char			**outfile;
		char			**append;
		char			**arg_cmd;
		char			*cmd_path;
	}	t_exec;
	GET_PIDS_AND_PIPES = Function for malloc pipes and pids variable in data
						 for the final execution.
	EXEC = Function for the final execution :
		Set all redirection, exec builtin if the token contain a builtin,
		else exec a child process and use execve for execute the command.
*/

void	execution(t_data *data)
{
	t_token	*current;

	current = data->lst_token;
	set_nbr_of_commands(data);
	init_exec(data);
	get_pids(data);
	exec(data, current);
}
