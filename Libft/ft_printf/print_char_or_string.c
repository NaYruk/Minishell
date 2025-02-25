/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_or_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:08:45 by mmilliot          #+#    #+#             */
/*   Updated: 2024/10/29 17:08:45 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putchar(char c)
{
	int	ret;

	ret = write(1, &c, 1);
	return (ret);
}

int	ft_putstr(char *str)
{
	int	i;
	int	ret;
	int	count;

	ret = 0;
	count = 0;
	if (!str)
	{
		ret = write(1, "(null)", 6);
		return (ret);
	}
	i = 0;
	while (str[i] != '\0')
	{
		ret = write(1, &str[i], 1);
		if (ret == -1)
		{
			count = -1;
			return (count);
		}
		count += ret;
		i++;
	}
	return (count);
}
