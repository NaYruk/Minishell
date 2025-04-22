/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_decimal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 07:06:07 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:11:44 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_putnbr_unsigned(unsigned int nbr, int *count)
{
	int	ret;

	if (nbr >= 10)
	{
		ft_putnbr_unsigned(nbr / 10, count);
	}
	ret = ft_putchar((nbr % 10) + '0');
	if (ret == -1)
	{
		*count = -1;
		return ;
	}
	*count += ret;
}

static	void	equal_to_int_min(int nbr, int **count)
{
	int	ret;

	ret = 0;
	if (nbr == INT_MIN)
	{
		ret = write (1, "-2147483648", 11);
		if (ret == -1)
		{
			**count = -1;
			return ;
		}
		**count += ret;
		return ;
	}
}

static void	ft_putnbr(int nbr, int *count)
{
	int	ret;

	equal_to_int_min(nbr, &count);
	if (*count == -1 || nbr == INT_MIN)
		return ;
	if (nbr < 0)
	{
		nbr *= -1;
		ret = ft_putchar('-');
		if (ret == -1)
		{
			*count = -1;
			return ;
		}
		*count += ret;
	}
	if (nbr >= 10)
		ft_putnbr(nbr / 10, count);
	ret = ft_putchar((nbr % 10) + '0');
	if (ret == -1)
	{
		*count = -1;
		return ;
	}
	*count += ret;
}

int	print_unsigned_nbr(unsigned int nbr)
{
	int	count;

	count = 0;
	ft_putnbr_unsigned(nbr, &count);
	return (count);
}

int	print_int(int nbr)
{
	int	count;

	count = 0;
	ft_putnbr(nbr, &count);
	return (count);
}
