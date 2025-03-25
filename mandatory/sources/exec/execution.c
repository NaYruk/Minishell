/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:49:08 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/25 02:58:34 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* WAIT_ALL = After the execution, we wait all child process. */

void	wait_all(t_data *data, int nbr_of_fork)
{
	while (nbr_of_fork >= 0)
	{
		if (waitpid(data->pids[nbr_of_fork], &data->exit_status, 0) == -1)
		{
			perror("WAITPID");
			error(data);
			return ;
		}
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
		nbr_of_fork--;
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

/*
	CHECK_DIR = Function to verify if a command path is a directory.

	This function checks if the command path specified in data->exec->cmd_path is a
	directory. If the path is a directory, it prints an error message and sets the
	exit status to 126. If the path is not a directory, the function returns 0.
*/

int	check_dir(t_data *data)
{
	struct stat	stat_file;

	stat(data->exec->cmd_path, &stat_file);
	if (S_ISDIR(stat_file.st_mode))
	{
		ft_putstr_fd(data->exec->cmd_path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		data->exit_status = 126;
		return (-1);
	}
	return (0);
}

/*
	EXEC_BUILD_OR_CMD = Function for exec a builtin if the token is a builtin
						exec other cmd if the token is not a builtin.
	
	In the case of a builtin, setup the redirections, and exec the builtin.
	In the case of an other command, create a child process, setup the
	redirections in the child, and exec the command with execve.
*/

void	exec_build_or_cmd(t_data *data, int *cmd_process, int *nbr_of_fork)
{
	if (exec_build(data->exec->arg_cmd[0]) == 1)
	{
		if (setup_redirection(data, *cmd_process) != -1)
			exec_builtin(data);
		dup2(data->stdout_backup, STDOUT_FILENO);
		dup2(data->stdin_backup, STDIN_FILENO);
	}
	else
	{
		if (check_dir(data) == -1)
			return ;
		data->pids[++(*nbr_of_fork)] = fork();
		if (data->pids[*nbr_of_fork] == 0)
			child_process(data, *cmd_process);
	}
	(*cmd_process)++;
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

void	exec(t_data *data, t_token *current)
{
	int	cmd_process;
	int	nbr_of_fork;

	cmd_process = 0;
	nbr_of_fork = -1;
	set_pipes(data);
	data->stdin_backup = dup(STDIN_FILENO);
	data->stdout_backup = dup(STDOUT_FILENO);
	// GET HEREDOC AND EXEC HEREDOC FOR THE FUTUR REDIRECTION ? 
	while (current != NULL)
	{
		if (set_exec_struct(data, &current) == -1)
		{
			free_exec_struct(data);
			break ;
		}
		exec_build_or_cmd(data, &cmd_process, &nbr_of_fork);
		free_exec_struct(data);
	}
	close_pipes(data);
	close(data->stdout_backup);
	close(data->stdin_backup);
	wait_all(data, nbr_of_fork);
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
	if (data->nbr_of_command == 0)
		return ;
	init_exec(data);
	get_pids_and_pipes(data);
	exec(data, current);
	free(data->pipes);
	free(data->pids);
	free(data->exec);
}
