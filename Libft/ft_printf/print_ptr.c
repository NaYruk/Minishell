/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 07:46:40 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:11:41 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	ft_convert_hexa(char *base, unsigned long long adresse, int *count)
{
	int	ret;

	if (adresse >= 16)
	{
		ft_convert_hexa(base, adresse / 16, count);
	}
	ret = ft_putchar(base[adresse % 16]);
	if (ret == -1)
	{
		*count = -1;
		return ;
	}
	*count += ret;
}

int	print_ptr(void *ptr)
{
	unsigned long long	decimal_adresse;
	char				*base;
	int					count;
	int					ret;

	count = 0;
	if (!ptr)
	{
		ret = write(1, "(nil)", 5);
		return (ret);
	}
	base = (char *)malloc(sizeof(char) * 17);
	if (base != NULL)
	{
		ft_memcpy(base, "0123456789abcdef", 17);
		decimal_adresse = (unsigned long long)ptr;
		ret = write(1, "0x", 2);
		if (ret == -1)
			return (-1);
		count += ret;
		ft_convert_hexa(base, decimal_adresse, &count);
		free(base);
	}
	return (count);
}
