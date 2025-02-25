/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:33:27 by marcmilliot       #+#    #+#             */
/*   Updated: 2024/11/29 11:55:19 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	search_new_line(char *stock)
{
	size_t	i;

	if (!stock)
		return (0);
	i = 0;
	while (stock[i] != '\0')
	{
		if (stock[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strle(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoinn(char *buff, char *stock)
{
	char	*new_stock;

	new_stock = NULL;
	if (stock == NULL)
	{
		stock = malloc(sizeof(char));
		if (!stock)
			return (NULL);
		stock[0] = '\0';
	}
	new_stock = malloc(sizeof(char) * (ft_strle(buff) + ft_strle(stock) + 1));
	if (!new_stock)
	{
		free_stock(&stock);
		return (NULL);
	}
	put_buff_stock_in_new_stock(&new_stock, stock, buff);
	free(stock);
	return (new_stock);
}

void	put_buff_stock_in_new_stock(char **new_stock, char *stock, char *buff)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (stock[i] != '\0')
	{
		(*new_stock)[i] = stock[i];
		i++;
	}
	while (buff[j] != '\0')
	{
		(*new_stock)[i] = buff[j];
		i++;
		j++;
	}
	(*new_stock)[i] = '\0';
}

char	*free_stock(char **stock)
{
	free(*stock);
	*stock = NULL;
	return (NULL);
}
