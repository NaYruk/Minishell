/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:40:33 by mmilliot          #+#    #+#             */
/*   Updated: 2025/03/04 13:24:21 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/* define for each token, it is for facilitate the parsing and execution. */
# define PIPE 1
# define CMD 2
# define HEREDOC 3
# define APPEND 4
# define INFILE 5
# define OUTFILE 6
# define OR 7
# define AND 8
# define ARG 9
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
}	t_token;

#endif