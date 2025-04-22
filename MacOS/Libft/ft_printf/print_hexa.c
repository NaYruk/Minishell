/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:09:30 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/25 12:11:38 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	void	ft_convert_hexa(char *base, unsigned int nbr, int *count)
{
	int	ret;

	if (nbr >= 16)
	{
		ft_convert_hexa(base, nbr / 16, count);
	}
	ret = ft_putchar(base[nbr % 16]);
	if (ret == -1)
	{
		*count = -1;
		return ;
	}
	*count += ret;
}

int	print_hexa_capital(unsigned int nbr)
{
	char	*base;
	int		count;

	count = 0;
	base = (char *)malloc(sizeof(char) * 17);
	if (base != NULL)
	{
		ft_memcpy(base, "0123456789ABCDEF", 17);
		ft_convert_hexa(base, nbr, &count);
		free(base);
	}
	return (count);
}

int	print_hexa_tiny(unsigned int nbr)
{
	char	*base;
	int		count;

	count = 0;
	base = (char *)malloc(sizeof(char) * 17);
	if (base != NULL)
	{
		ft_memcpy(base, "0123456789abcdef", 17);
		ft_convert_hexa(base, nbr, &count);
		free(base);
	}
	return (count);
}
