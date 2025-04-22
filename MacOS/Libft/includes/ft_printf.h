/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmilliot <mmilliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:08:58 by mmilliot          #+#    #+#             */
/*   Updated: 2024/10/29 17:08:58 by mmilliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_printf(const char *str, ...)__attribute__((format(printf, 1, 2)));
int		print_unsigned_nbr(unsigned int nbr);
int		print_int(int nbr);
int		print_ptr(void *ptr);
int		print_hexa_capital(unsigned int nbr);
int		print_hexa_tiny(unsigned int nbr);
int		ft_putchar(char c);
int		ft_putstr(char *str);

#endif
