/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:53:35 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/29 12:05:19 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

size_t	ft_strle(const char *s);
int		search_new_line(char *stock);
char	*ft_strjoinn(char *buff, char *stock);
char	*get_next_line(int fd);
char	*free_stock(char **stock);
void	put_buff_stock_in_new_stock(char **new_stock, char *stock, char *buff);

#endif