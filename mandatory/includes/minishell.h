/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcmilliot <marcmilliot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:59:31 by mmilliot          #+#    #+#             */
/*   Updated: 2025/04/23 02:55:38 by marcmilliot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
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

extern int	g_signal;

typedef struct s_signal_flags
{
	int	ctrl_c_displayed;
	int	quit_displayed;
}	t_signal_flags;

typedef struct s_escaped_char
{
	char	*escaped_line;
	char	*old_line;
	int		start;
	int		end;
	int		index;
}	t_escaped_char;

typedef struct s_env
{
	char	*name;
	char	*value;
	char	*existing_value;
	char	*new_value;
	int		available;
}	t_env;

/* Chained List Garbage collector */
typedef struct s_garbage_collector
{
	void						**memory;
	int							is_array;
	struct s_garbage_collector	*next;
}	t_garb_c;

typedef struct s_exec_redir
{
	int					type;
	int					position;
	char				*arg;
	struct s_exec_redir	*next;
	struct s_exec_redir	*prev;
}	t_exec_redir;

/* Struct for the execution of each command */
typedef struct s_exec
{
	t_exec_redir	*t_exec_redir;
	char			**arg_cmd;
	char			*cmd_path;
}	t_exec;

/* Struct data, she contain all struct / variable for Minishell */
typedef struct s_data
{
	char		*prompt;
	char		**env;
	pid_t		*pids;
	int			*heredoc_fd;
	int			nbr_heredoc;
	int			hd_index;
	int			heredoc_in_pipe;
	int			old_read_pipe;
	int			current_pipe[2];
	int			error_built;
	bool		operator;
	bool		simple_q;
	bool		double_q;
	char		quotes_char;
	int			exit_status;
	int			nbr_of_command;
	int			part_of_line;
	int			stdout_backup;
	int			stdin_backup;
	t_exec		*exec;
	t_garb_c	*g_c;
	t_token		*lst_token;
}	t_data;

/* Function for all initialization */
t_data	*init_all(char **envp);

/* Function for write an error and return the program */
void	malloc_error(t_data *data);
void	error(t_data *data, char *error);
void	ft_free_env(char **tmp);

/* 
	Functions for manipulate the memory with a garbage collector
	Each memory allocation need to be stock in the garbage collector with
	a cast in (void **).
*/
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
int		check_validity_cmd(t_data *data, t_token **current);
void	check_escaped_content(t_data *data, char **line,
			int *i, char **new_line);
void	stock_char(t_data *data, char **new_line, char c);
int		expand_till(t_data *data, char **new_line, char *line, int *i);
void	expand_dollar(t_data *data, char **new_line, char *prompt, int *i);

/* Main Function for the tokenization ! */
int		tokenization(t_data *data);

/* Functions for add a new token in the chained list */
void	add_new_token(t_data *data, t_token **lst, char *line);
void	free_token(t_data *data);

/* Function for check any error after the tokenisation */
int		check_rafter(t_data *data, t_token *current);
int		check_pipes(t_data *data, t_token *current);
void	replace_dollars(t_data *data, char **line);
int		token_error(t_data *data, char *line, bool newline);

/* Functions for built-in commands */
int		ft_pwd(t_data *data);
int		ft_exit(t_data *data, char **args_cmd);
int		ft_cd(t_data *data, char **args_cmd);
int		ft_env(t_data *data);
int		ft_echo(t_data *data, char **args_cmd);
int		ft_unset(t_data *data, char **args_cmd);
int		ft_export(t_data *data, char **args_cmd);
char	*ft_getenv(t_data *data, char *name, int *available);
void	ft_update_env(t_data *data, char *name, char *value);
void	ft_delete_env(t_data *data, char *name);
void	ft_add_new_env(t_data *data, char *name, char *value);
void	ft_realloc_env(t_data *data, size_t new_size);
int		exec_builtin(t_data *data, char **args_cmd, int cmd_process);

/* Functions to export builtin */

void	ft_error_name(char *str);
int		ft_verif_name(char *str);
void	ft_extract_name_value(char *str, char **name, char **value);
char	**ft_duplicate_env(t_data *data);
void	ft_display_env(char **tmp);

/* Function for the execution of commands */
void	execution(t_data *data);
void	init_exec(t_data *data);
void	free_exec_struct(t_data *data);
void	get_pids(t_data *data);
void	set_nbr_of_commands(t_data *data);
void	get_args_cmd(t_data *data, t_token *current);
int		exec_build(char *line);
int		get_cmd_path(t_data *data, t_token **current);
int		set_outfile(t_data *data, t_token *current);
int		set_append(t_data *data, t_token *current);
int		set_infile(t_data *data, t_token *current);
int		set_heredoc(t_data *data, t_token *current);
bool	last_heredoc(t_exec_redir *current);
int		exec_heredoc(t_data *data);
int		child_process(t_data *data, int i);
int		setup_redirection(t_data *data, int cmd_process);
int		set_exec_struct(t_data *data, t_token **current);
void	add_new_redir_node(t_data *data, t_exec_redir **lst,
			char *line, int type);
void	exec_build_or_cmd(t_data *data, int *cmd_process, int *nbr_of_fork);
void	wait_all(t_data *data, int nbr_of_fork);
void	free_all(t_data *data);
void	update_exit_status(t_data *data);
void	redirect_pipes(t_data *data, int cmd_process);
void	close_heredoc_fd(t_data *data);
void	malloc_heredoc_fd(t_data *data, int nbr);
int		nbr_of_heredoc(t_data *data);
bool	catch_signal(t_data *data, char *line, char *delimiter);
bool	last_heredoc(t_exec_redir *current);

#endif