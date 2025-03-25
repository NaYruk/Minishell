/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:59:31 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/25 15:50:10 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*Library already used
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stddef.h>
# include <stdint.h> */

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

typedef struct s_exec
{
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
	int			(*pipes)[2];
	bool		operator;
	bool		simple_q;
	bool		double_q;
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
void	sig_handler(void);

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
void	if_dollar(t_data *data, char **new_line, char *prompt, int *i);
int		token_error(t_data *data, char *line);

/* Functions for built-in commands */
int		ft_pwd(t_data *data);
int		ft_exit(t_data *data);
int		ft_cd(t_data *data);
int		ft_env(t_data *data);
int		ft_echo(t_data *data);
int		ft_unset(t_data *data);
int		ft_export(t_data *data);
char	*ft_getenv(t_data *data, char *name);
void	ft_update_env(t_data *data, char *name, char *value);
void	ft_delete_env(t_data *data, char *name);
int		ft_verif_name(char *str);
int		exec_builtin(t_data *data);

/* Function for the execution of commands */
void	execution(t_data *data);
void	init_exec(t_data *data);
void	free_exec_struct(t_data *data);
void	get_pids_and_pipes(t_data *data);
void	set_nbr_of_commands(t_data *data);
void	get_args_cmd(t_data *data, t_token *current);
void	get_cmd_path(t_data *data, t_token **current);
void	set_pipes(t_data *data);
void	close_pipes(t_data *data);
int		child_process(t_data *data, int i);
int		setup_redirection(t_data *data, int cmd_process);
int		set_exec_struct(t_data *data, t_token **current);

#endif