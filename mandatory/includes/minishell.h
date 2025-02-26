/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:59:31 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/26 14:58:13 by mmilliot         ###   ########.fr       */
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


/* Libft Headers */
# include "../../Libft/includes/ft_printf.h"
# include "../../Libft/includes/get_next_line.h"
# include "../../Libft/includes/libft.h"



/* Chained List Garbage collector */
typedef struct	s_garbage_collector
{
	void						**memory;
	struct s_garbage_collector	*next;
} t_garbage_collector;



/* Struct data, she contain all struct / variable for Minishell */
typedef struct	s_data
{
	char *prompt;
	char **split;
	int	 nbr_pipes;
	t_garbage_collector *g_c;
} t_data;



/* Function for all initialization */
t_data	*init_all(void);

/* 
	Functions for manipulate the memory with a garbage collector
	Each memory allocation need to be stock in the garbage collector with
	a cast in (void **).
*/
void	init_garbage_collector(t_data *data);
void	add_new_g_b_node(t_data *data, t_garbage_collector **g_c, void **memory);
void	free_garbage(t_data *data);

#endif