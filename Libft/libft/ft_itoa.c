/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:34:51 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:12:42 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <limits.h>

static size_t	size_str(int nbr, size_t size)
{
	size = 0;
	if (nbr < 0)
	{
		size++;
		nbr *= -1;
	}
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}

static size_t	ten_div(size_t size)
{
	size_t	result;

	result = 10;
	while (size - 2 > 0)
	{
		result *= 10;
		size--;
	}
	return (result);
}

static char	*min_value(void)
{
	char	*str ;

	str = (char *)malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

static int	if_int_neg(char *str, size_t *size, int *n)
{
	int	i;

	i = 0;
	if (*n < 0)
	{
		str[i++] = '-';
		*n *= -1;
		(*size)--;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	size = size_str(n, size);
	if (n == INT_MIN)
		return (min_value());
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = if_int_neg(str, &size, &n);
	while (size > 0)
	{
		if (size > 1)
			str[i++] = ((n / ten_div(size)) % 10 + '0');
		else
			str[i++] = (n % 10) + '0';
		size--;
	}
	str[i] = '\0';
	return (str);
}
