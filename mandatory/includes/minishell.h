/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:59:31 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/04 17:53:26 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*Library alredy used
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

/* Libft Headers */
# include "../../Libft/includes/ft_printf.h"
# include "../../Libft/includes/get_next_line.h"
# include "../../Libft/includes/libft.h"
# include "./define.h"

/* Chained List Garbage collector */
typedef struct s_garbage_collector
{
	void						**memory;
	int							is_array;
	struct s_garbage_collector	*next;
}	t_garb_c;

/* Struct data, she contain all struct / variable for Minishell */
typedef struct s_data
{
	char		*prompt;
	char		**env;
	bool		operator;
	char		*name_op;
	t_garb_c	*g_c;
	t_token		*lst_token;
}	t_data;

/* Function for all initialization */
t_data	*init_all(char **envp);

/* Function for write an error and return the program */
void	malloc_error(t_data *data);

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
void	cut_the_line(t_data *data);
/* Main Function for the tokenization ! */
void	tokenization(t_data *data);

/* Function for add a new token in the chained list */
void	add_new_token(t_data *data, t_token **lst, char *line, char qc);

void	free_token(t_data *data);

#endif