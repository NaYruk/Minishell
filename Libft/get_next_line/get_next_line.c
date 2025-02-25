/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:40:05 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/29 11:53:12 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static char	*read_and_stock(char *stock, int fd)
{
	ssize_t	value_read;
	char	*buff;

	value_read = 1;
	while (!search_new_line(stock) && value_read > 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (free_stock(&stock));
		value_read = read(fd, buff, BUFFER_SIZE);
		if (value_read == -1)
		{
			free(buff);
			return (free_stock(&stock));
		}
		if (value_read == 0)
		{
			free(buff);
			break ;
		}
		buff[value_read] = '\0';
		stock = ft_strjoinn(buff, stock);
		free(buff);
	}
	return (stock);
}

static char	*get_final_line(char *stock)
{
	char	*final_line;
	size_t	i;
	size_t	j;

	if (!stock)
		return (NULL);
	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	if (stock[i] == '\n')
		i++;
	final_line = malloc(sizeof(char) * (i + 1));
	if (!final_line)
		return (NULL);
	j = 0;
	while (i > j)
	{
		final_line[j] = stock[j];
		j++;
	}
	final_line[i] = '\0';
	return (final_line);
}

static char	*update_stock(char *stock)
{
	char	*temp;
	size_t	i;
	size_t	j;

	if (!stock)
		return (NULL);
	i = 0;
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	if (stock[i] == '\n')
		i++;
	if (stock[i] == '\0')
		return (free_stock(&stock));
	temp = malloc(sizeof(char) * (ft_strle(stock) - i + 1));
	if (!temp)
		return (free_stock(&stock));
	j = 0;
	while (stock[i] != '\0')
		temp[j++] = stock[i++];
	temp[j] = '\0';
	free_stock(&stock);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*stock[MAX_FD] = {NULL};
	char		*final_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	final_line = NULL;
	stock[fd] = read_and_stock(stock[fd], fd);
	if (!stock[fd])
		return (NULL);
	final_line = get_final_line(stock[fd]);
	if (!final_line)
		return (free_stock(&(stock[fd])));
	stock[fd] = update_stock(stock[fd]);
	return (final_line);
}
