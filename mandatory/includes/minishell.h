/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melvin <melvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:59:31 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/01 22:10:52 by melvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

/* Libft Headers */
# include "../../Libft/includes/ft_printf.h"
# include "../../Libft/includes/get_next_line.h"
# include "../../Libft/includes/libft.h"
# include "./define.h"

# define BUF_SIZE 1024

/* Chained List Garbage collector */
typedef struct s_garbage_collector
{
	void						**memory;
	int							is_array;
	struct s_garbage_collector	*next;
}	t_garb_c;

/* Struct for the execution of each command */
typedef struct s_exec
{
	int				nbr_infile;
	int				nbr_outfile;
	int				nbr_append;
	int				nbr_heredoc;
	int				last_heredoc_fd;
	char			**infile;
	char			**outfile;
	char			**append;
	char			**heredoc;
	char			**arg_cmd;
	char			*cmd_path;
}	t_exec;

/* Struct data, she contain all struct / variable for Minishell */
typedef struct s_data
{
	char		*prompt;
	char		**env;
	pid_t		*pids;
	int			old_pipe[2];
	int			current_pipe[2];
	bool		*is_builtin_cmd;
	bool		operator;
	bool		simple_q;
	bool		double_q;
	char		quotes_char;
	int			exit_status;
	int			nbr_of_command;
	int			stdout_backup;
	int			stdin_backup;
	t_exec		*exec;
	t_garb_c	*g_c;
	t_token		*lst_token;
}	t_data;

/* Function for all initialization */
t_data	*init_all(char **envp);

/* Functions utils for Manipulate chained list */
t_token	*last_node(t_token *lst);

/* Function for write an error and return the program */
void	malloc_error(t_data *data);
void	error(t_data *data);

/* 
	Functions for manipulate the memory with a garbage collector
	Each memory allocation need to be stock in the garbage collector with
	a cast in (void **).
*/
void	init_garbage_collector(t_data *data);
void	add_g_c_node(t_data *data, t_garb_c **g_c, void **memory, bool is_arr);
void	free_garbage(t_data *data);

/* Function for manage signals */
void	setup_signals_interactive(void);
void	setup_signals_heredoc(void);
void	setup_signals_execution(void);

/* Functions for command-line tokenization */
int		check_quotes(t_data *data, char *str);
int		ft_is_quote(char c);
int		ft_is_white_spaces(char c);
int		cut_the_line(t_data *data);
int		is_operator(t_data *data, int *i, char **line);
bool	operator(char c);

/* Main Function for the tokenization ! */
int		tokenization(t_data *data);

/* Functions for add a new token in the chained list */
void	add_new_token(t_data *data, t_token **lst, char *line);
void	free_token(t_data *data);

/* Function for check any error after the tokenisation */
int		check_rafter(t_data *data);
int		check_pipes(t_data *data);
void	replace_dollars(t_data *data, char **line);
int		token_error(t_data *data, char *line);

/* Functions for built-in commands */
int		ft_pwd(t_data *data);
int		ft_exit(t_data *data, char **args_cmd);
int		ft_cd(t_data *data);
int		ft_env(t_data *data);
int		ft_echo(t_data *data, char **args_cmd);
int		ft_unset(t_data *data, char **args_cmd);
int		ft_export(t_data *data, char **args_cmd);
char	*ft_getenv(t_data *data, char *name, int *available);
void	ft_update_env(t_data *data, char *name, char *value);
void	ft_delete_env(t_data *data, char *name);
int		ft_verif_name(char *str);
int		exec_builtin(t_data *data, char **args_cmd, int cmd_process);

void	ft_add_new_env(t_data *data, char *name, char *value);
void	ft_extract_name_value(char *str, char **name, char **value);

char	**ft_duplicate_env(t_data *data);
void	ft_sort_env(char **env);
void	ft_display_env(char **tmp);
void	ft_free_tmp(char **tmp);

/* Function for the execution of commands */
void	execution(t_data *data);
void	init_exec(t_data *data);
void	free_exec_struct(t_data *data);
void	get_pids(t_data *data);
void	set_nbr_of_commands(t_data *data);
void	get_args_cmd(t_data *data, t_token *current);
int		exec_build(char *line);
int		get_cmd_path(t_data *data, t_token **current);
int		get_nbr_redir(t_data *data, t_token *current);
int		set_outfile_array(t_data *data, t_token *current, int *k);
int		set_append_array(t_data *data, t_token *current, int *j);
int		set_infile_heredoc_array(t_data *data, t_token *current, int *i, int *l);
int		exec_heredoc(t_data *data);
int		child_process(t_data *data, int i);
int		setup_redirection(t_data *data, int cmd_process, bool builtin);
int		set_exec_struct(t_data *data, t_token **current);

#endif