/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:07:31 by mmilliot          #+#    #+#             */
/*   Updated: 2024/11/09 16:24:38 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	print_arg(va_list *args, char letter, int *count, int ret)
{
	if (letter == 'c')
		ret = ft_putchar(va_arg(*args, int));
	else if (letter == 's')
		ret = ft_putstr(va_arg(*args, char *));
	else if (letter == 'p')
		ret = print_ptr(va_arg(*args, void *));
	else if (letter == 'd')
		ret = print_int(va_arg(*args, int));
	else if (letter == 'i')
		ret = print_int(va_arg(*args, int));
	else if (letter == 'u')
		ret = print_unsigned_nbr(va_arg(*args, unsigned int));
	else if (letter == 'x')
		ret = print_hexa_tiny(va_arg(*args, unsigned int));
	else if (letter == 'X')
		ret = print_hexa_capital(va_arg(*args, unsigned int));
	else if (letter == '%')
		ret = ft_putchar('%');
	if (ret == -1)
	{
		*count = -1;
		return ;
	}
	*count += ret;
}

void	parse_string(va_list *args, const char *str, int *count_print, int ret)
{
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			print_arg(args, *str, count_print, ret);
			if (*count_print == -1 || *str == '\0')
			{
				if (*str == '\0')
					*count_print = -1;
				return ;
			}
		}
		else
		{
			ret = ft_putchar(*str);
			if (ret == -1)
			{
				*count_print = -1;
				return ;
			}
			*count_print += ret;
		}
		str++;
	}
}

int	ft_printf(const char *str, ...)
{
	int		count_print;
	va_list	args;

	if (!str)
		return (-1);
	count_print = 0;
	va_start(args, str);
	parse_string(&args, str, &count_print, 0);
	va_end(args);
	return (count_print);
}
