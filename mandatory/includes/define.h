/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcotonea <mcotonea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:40:33 by mmilliot          #+#    #+#             */
/*   Updated: 2025/02/28 16:31:06 by mcotonea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define PIPE 1
# define CMD 2
# define HEREDOC 3
# define APPEND 4
# define INFILE 5
# define OUTFILE 6
# define REDIR 7
# define OR 8
# define AND 9
# define ARG 10

# define SIMPLE_QUOTES '\''
# define DOUBLE_QUOTES '"'

typedef struct s_token {
	char			*line;
	int				token;
	struct s_token	*next;
}	t_token;

#endif