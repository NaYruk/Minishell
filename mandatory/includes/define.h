/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:40:33 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/04 13:40:23 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/* define for each token, it is for facilitate the parsing and execution. */
# define HEREDOC 1
# define INFILE 2
# define PIPE 3
# define APPEND 4
# define OUTFILE 5
# define OR 6
# define AND 7
# define ARG 8
# define CMD 9
# define OTHER 10

/* Define for the Quotes */
# define SIMPLE_QUOTES '\''
# define DOUBLE_QUOTES '"'

/* Struct for each token, a token is a part of the prompt */

typedef struct s_token
{
	char			*line;
	int				token;
	int				status;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

#endif